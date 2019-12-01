//
// Created by HUANG WEN JUN on 2019/11/30.
//

#pragma once
#include "../../util/json.h"
#include <QtCore>

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;

    struct APITopPlayListItemData {
        Q_GADGET
        Q_PROPERTY(int id MEMBER id)
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(long trackNumberUpdateTime MEMBER trackNumberUpdateTime)
        Q_PROPERTY(int status MEMBER status)
        Q_PROPERTY(int userId MEMBER userId)
        Q_PROPERTY(long createTime MEMBER createTime)
        Q_PROPERTY(long updateTime MEMBER updateTime)
        Q_PROPERTY(int subscribedCount MEMBER subscribedCount)
        Q_PROPERTY(int commentCount MEMBER commentCount)
        Q_PROPERTY(QString copywriter MEMBER copywriter)
        Q_PROPERTY(QString tag MEMBER tag)
      public:
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

        static APITopPlayListItemData fromJsonValue(const QJsonValue& jsonValue);
    };

    struct APITopPlayListHighQualityData {
        Q_GADGET
        Q_PROPERTY(int total MEMBER total)
        Q_PROPERTY(long lasttime MEMBER lasttime)
        Q_PROPERTY(bool more MEMBER more)
        Q_PROPERTY(int code MEMBER code)
        Q_PROPERTY(QVariantList playlists MEMBER playlists)
      public:
        int total;
        long lasttime;
        bool more;
        int code;
        QVariantList playlists;

        static APITopPlayListHighQualityData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API
