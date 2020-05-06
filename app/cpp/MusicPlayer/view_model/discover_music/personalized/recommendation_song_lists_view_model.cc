//
// Created by rick on 2019/11/10.
//

#include "recommendation_song_lists_view_model.h"
#include "api.h"
#include "util.h"
#include <QtCore>

namespace MusicPlayer::ViewModel {
    using namespace MusicPlayer::API;
    using namespace MusicPlayer::Util;

    static QString kWeekDays[] = {
        QStringLiteral(u"星期一"),
        QStringLiteral(u"星期二"),
        QStringLiteral(u"星期三"),
        QStringLiteral(u"星期四"),
        QStringLiteral(u"星期五"),
        QStringLiteral(u"星期六"),
        QStringLiteral(u"星期日"),
    };

    class RecommendationSongsListModel : public QAbstractListModel {
        Q_OBJECT
      public:
        using ModeItem = std::variant<EveryDayRecommendation, APIPersonalizedItemData>;
        enum Roles { ImageUrl = Qt::UserRole + 1, Id, Name, PlayCount, Tips, Today, Weekday, Kind };

        explicit RecommendationSongsListModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& index) const override;

        QHash<int, QByteArray> roleNames() const override;

        QVariant data(const QModelIndex& index, int role) const override;

        void setRecommendationSongListsData(const APIPersonalizedData& data) {
            beginResetModel();
            _songsList.clear();
            _songsList.append(EveryDayRecommendation{data.result.last().picUrl});
            std::copy(data.result.cbegin(), data.result.cend() - 1, std::back_inserter(_songsList));
            endResetModel();
        }

      private:
        QVector<ModeItem> _songsList;
    };

    QVariant RecommendationSongsListModel::data(const QModelIndex& index, int role) const {
        const auto& item = _songsList[index.row()];

        return std::visit(
            [=](const auto& value) -> QVariant {
                if constexpr (std::is_convertible_v<decltype(value), APIPersonalizedItemData>) {
                    if (role == Roles::ImageUrl)
                        return value.picUrl;
                    if (role == Roles::Id)
                        return value.id;
                    if (role == Roles::Name)
                        return value.name;
                    if (role == Roles::PlayCount) {
                        if (value.playCount > 10000)
                            return QString(QStringLiteral(u"%1万")).arg(value.playCount / 10000);
                        else
                            return QString("%1").arg(value.playCount);
                    }
                    if (role == Roles::Kind)
                        return RecommendationSongListsViewModel::Normal;

                    return QVariant();
                } else {
                    if (role == Roles::Id)
                        return -1;
                    if (role == Roles::Name)
                        return value.name;
                    if (role == Roles::Kind)
                        return RecommendationSongListsViewModel::EveryDay;
                    if (role == Roles::Tips)
                        return value.tips;
                    if (role == Roles::Today)
                        return value.today.date().day();
                    if (role == Roles::Weekday)
                        return kWeekDays[value.today.date().dayOfWeek() - 1];
                    if (role == Roles::ImageUrl)
                        return value.imageUrl;
                    return QVariant();
                }
            },
            item);
    }

    QHash<int, QByteArray> RecommendationSongsListModel::roleNames() const {
        QHash<int, QByteArray> names;

        names[Roles::ImageUrl]  = "imageUrl";
        names[Roles::Id]        = "id";
        names[Roles::Name]      = "name";
        names[Roles::PlayCount] = "playCount";
        names[Roles::Tips]      = "tips";
        names[Roles::Today]     = "today";
        names[Roles::Weekday]   = "weekday";
        names[Roles::Kind]      = "kind";

        return names;
    }

    int RecommendationSongsListModel::rowCount(const QModelIndex& index) const {
        int c = _songsList.size();
        return c;
    }

    RecommendationSongsListModel::RecommendationSongsListModel(QObject* parent) : QAbstractListModel{parent} {}

    RecommendationSongListsViewModel::RecommendationSongListsViewModel(QObject* parent) : BaseStateViewModel{parent} {
        _songsModel = new RecommendationSongsListModel(this);
    }

    void RecommendationSongListsViewModel::loadData() {
        if (std::get_if<LoadingState>(&_state))
            return;

        setState(LoadingState{});
        auto api = MusicAPI::instance();
        auto response = api->personalized(10);
        connect(response,
                &APIResponseHandler<APIPersonalizedData>::finished,
                this,
                &RecommendationSongListsViewModel::personalizedResponse);
    }

    void RecommendationSongListsViewModel::personalizedResponse(const APIResponse<APIPersonalizedData>& reply) {
        std::visit(
            [=](const auto& value) {
                if constexpr (std::is_convertible_v<decltype(value), APIPersonalizedData>) {
                    _songsModel->setRecommendationSongListsData(value);
                    setState(ReadyState{});
                } else {
                    // errors
                }
            },
            reply);
    }

    void RecommendationSongListsViewModel::componentComplete() { loadData(); }

    QAbstractListModel* RecommendationSongListsViewModel::songLists() { return _songsModel; }
} // namespace MusicPlayer::ViewModel

#include "recommendation_song_lists_view_model.moc"
