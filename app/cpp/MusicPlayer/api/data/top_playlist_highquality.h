//
// Created by HUANG WEN JUN on 2019/11/30.
//

#pragma once
#include "../../util/json.h"
#include <QtCore>

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

        static APITopPlayListItemData fromJsonValue(const QJsonValue& jsonValue);
    };

    struct APITopPlayListHighQualityData {
        int total;
        long lasttime;
        bool more;
        int code;
        QVector<APITopPlayListItemData> playlists;

        static APITopPlayListHighQualityData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API
