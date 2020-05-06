//
// Created by rick on 2019/11/10.
//

#pragma once

#include <QAbstractListModel>
#include <QtCore/QDateTime>
#include <QtCore/QObject>
#include <QtQml/QQmlParserStatus>
#include <optional>
#include <variant>
#include "api.h"
#include "../../base_state_view_model.h"

namespace MusicPlayer::ViewModel {
    using namespace MusicPlayer::API;

    struct EveryDayRecommendation {
        QUrl imageUrl;
        QString name    = "每日歌曲推荐";
        QString tips    = "根据您的音乐口味生成每日更新";
        QDateTime today = QDateTime::currentDateTime();
    };

    class RecommendationSongsListModel;
    class RecommendationSongListsViewModel : public BaseStateViewModel, public QQmlParserStatus {
        Q_OBJECT
        Q_INTERFACES(QQmlParserStatus)
        Q_PROPERTY(QAbstractListModel* songLists READ songLists)
      public:
        enum ItemKind { Normal, EveryDay };

        Q_ENUM(ItemKind)

        explicit RecommendationSongListsViewModel(QObject* parent = nullptr);
        void componentComplete() override;
        void classBegin() override {}
        QAbstractListModel* songLists();

      private slots:
        void personalizedResponse(const APIResponse<APIPersonalizedData>& reply);
      private:
        void loadData();

        RecommendationSongsListModel* _songsModel;
    };

} // namespace MusicPlayer::ViewModels
