//
// Created by HUANG WEN JUN on 2019/11/30.
//

#pragma once
#include "../../util/json.h"
#include <QtCore>
#include "playlist_detail.h"

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;

    struct APITopPlayListItemData {
        int id;
        QString name;
        long trackNumberUpdateTime;
        int status;
        int userId;
        long createTime;
        long updateTime;
        int subscribedCount;
        int commentCount;
        QString copywriter;
        QString tag;
        QUrl coverImgUrl;
        APIPlayListDetailUser creator;
        int playCount;


        static APITopPlayListItemData fromJsonValue(const QJsonValue& jsonValue);
    };

    struct APITopPlayListData {
        int total;
        long lasttime;
        bool more;
        int code;
        QVector<APITopPlayListItemData> playlists;

        static APITopPlayListData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API
