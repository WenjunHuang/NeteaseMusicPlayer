//
// Created by rick on 2019/11/10.
//

#include "personalized_new_song_view_model.h"
#include "../util/executor.h"

namespace MusicPlayer::ViewModels {
    using namespace Util;
    PersonalizedNewSongListModel::PersonalizedNewSongListModel(QObject* parent) : QAbstractListModel{parent} {}

    QHash<int, QByteArray> PersonalizedNewSongListModel::roleNames() const {
        QHash<int, QByteArray> names;
        names[Roles::ImageUrl]             = "imageUrl";
        names[Roles::Artists]              = "artists";
        names[Roles::Id]                   = "id";
        names[Roles::IsCurrentSong]        = "isCurrentSong";
        names[Roles::IsSq]                 = "isSq";
        names[Roles::IsCurrentSongPlaying] = "isCurrentSongPlaying";
        names[Roles::MvId]                 = "mvId";
        names[Roles::Name]                 = "name";
        names[Roles::NameAlias]            = "nameAlias";
        return names;
    }

    int PersonalizedNewSongListModel::rowCount(const QModelIndex& index) const { return _data.size(); }

    QVariant PersonalizedNewSongListModel::data(const QModelIndex& index, int role) const {
        const auto& item = _data[index.row()];
        if (role == Roles::ImageUrl) {
            return item.song.album.picUrl;
        }
        if (role == Roles::Name)
            return item.song.name;
        if (role == Roles::Id)
            return item.song.id;
        if (role == Roles::NameAlias)
            return QStringList(item.song.alias.toList()).join(',');
        if (role == Roles::Artists) {
            QStringList artistNames;
            std::transform(
                item.song.artists.cbegin(), item.song.artists.cend(), std::back_inserter(artistNames), [](const auto& artist) {
                    return artist.template value<APIPersonalizedNewSongResultSongArtistData>().name;
                });
            return artistNames.join(" / ");
        }
        if (role == Roles::IsCurrentSong)
            return false;
        if (role == Roles::IsCurrentSongPlaying)
            return false;
        if (role == Roles::IsSq)
            return item.song.privilege.maxbr == 999000; // 最大质量格式
        if (role == Roles::MvId)
            return item.song.mvid;

        return {};
    }

    void PersonalizedNewSongListModel::setPersonalizedNewSongData(const APIPersonalizedNewSongData& data) {
        beginResetModel();
        _data.clear();
        std::transform(data.result.cbegin(), data.result.cend(), std::back_inserter(_data), [](const auto& var) {
            return var.template value<APIPersonalizedNewSongResultData>();
        });
        endResetModel();
    }

    PersonalizedNewSongViewModel::PersonalizedNewSongViewModel(QObject* parent) : QObject{parent} {
        _newSongModel = new PersonalizedNewSongListModel(this);
    }

    void PersonalizedNewSongViewModel::loadData() {
        if (_loading && !_loading->isReady())
            return;
        MusicAPI api;
        _loading = api.personalizedNewSong()
                       .via(AppExecutor::instance()->getMainExecutor().get())
                       .thenValue([this](const Response<APIPersonalizedNewSongData>& reply) {
                           std::visit(
                               [=](const auto& value) {
                                   if constexpr (std::is_convertible_v<decltype(value), APIPersonalizedNewSongData>) {
                                       _newSongModel->setPersonalizedNewSongData(value);
                                   } else {
                                       // errors
                                   }
                               },
                               reply);
                           return std::nullopt;
                       });
    }

    QAbstractListModel* PersonalizedNewSongViewModel::newSongListModel() const { return _newSongModel; }
} // namespace MusicPlayer::ViewModels
