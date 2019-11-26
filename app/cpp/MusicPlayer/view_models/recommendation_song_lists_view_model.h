//
// Created by rick on 2019/11/10.
//

#pragma once

#include <variant>
#include <QtCore/QObject>
#include <QtQml/QQmlParserStatus>
#include <QtCore/QDateTime>
#include <QAbstractListModel>
#include "../api/data/personalized.h"

namespace MusicPlayer::ViewModels {
    using namespace MusicPlayer::API;

    struct EveryDayRecommendation {
        QUrl imageUrl;
        QString name = "每日歌曲推荐";
        QString tips = "根据您的音乐口味生成每日更新";
        QDateTime today = QDateTime::currentDateTime();
    };


    class RecommendationSongsListModel;
    class RecommendationSongListsViewModel : public QObject, public QQmlParserStatus {
        Q_OBJECT
        Q_INTERFACES(QQmlParserStatus)
        Q_PROPERTY(QAbstractListModel *songLists READ songLists)
    public:
        enum ItemKind {
            Normal,
            EveryDay
        };

        Q_ENUM(ItemKind)

        explicit RecommendationSongListsViewModel(QObject *parent = nullptr);
        void componentComplete() override;
        void classBegin() override {}
        QAbstractListModel* songLists();

    private:
        void loadData();

        RecommendationSongsListModel *_songsModel;

    };

}



