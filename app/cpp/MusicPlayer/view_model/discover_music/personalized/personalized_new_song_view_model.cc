//
// Created by rick on 2019/11/10.
//

#include "personalized_new_song_view_model.h"
#include "util.h"

namespace MusicPlayer::ViewModel{
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
            std::transform(item.song.artists.cbegin(),
                           item.song.artists.cend(),
                           std::back_inserter(artistNames),
                           [](const auto& artist) { return artist.name; });
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
        _data.append(data.result);
        endResetModel();
    }

    PersonalizedNewSongViewModel::PersonalizedNewSongViewModel(QObject* parent) : BaseStateViewModel{parent} {
        _newSongModel = new PersonalizedNewSongListModel(this);
    }

    void PersonalizedNewSongViewModel::loadData() {
        if (auto state = std::get_if<LoadingState>(&_state)) {
            return;
        } else {
            setState(LoadingState{});

            auto api = MusicAPI::instance();
            auto response = api->personalizedNewSong();
            connect(response,
                    &APIResponseHandler<APIPersonalizedNewSongData>::finished,
                    this,
                    &PersonalizedNewSongViewModel::personalNewSongResult);
        }
    }

    void PersonalizedNewSongViewModel::personalNewSongResult(const APIResponse<APIPersonalizedNewSongData>& reply) {
        std::visit(
            [=](const auto& value) {
                if constexpr (std::is_convertible_v<decltype(value), APIPersonalizedNewSongData>) {
                    _newSongModel->setPersonalizedNewSongData(value);
                    setState(ReadyState{});
                } else {
                    // errors
                }
            },
            reply);
    }

    QAbstractListModel* PersonalizedNewSongViewModel::newSongListModel() const { return _newSongModel; }
} // namespace MusicPlayer::ViewModels
