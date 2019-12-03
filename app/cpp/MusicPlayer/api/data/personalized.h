#pragma once

#include <QtCore>

namespace MusicPlayer::API {

    struct APIPersonalizedItemData {
        int id;
        int type;
        QString name;
        QString copywriter;
        QUrl picUrl;
        bool canDislike;
        int trackNumberUpdateTime;
        double playCount;
        int trackCount;
        bool highQuality;
        QString alg;

        bool operator==(const APIPersonalizedItemData& other) const;
        bool operator!=(const APIPersonalizedItemData& other) const;

        static APIPersonalizedItemData fromJsonValue(const QJsonValue& json);
    };

    struct APIPersonalizedData {
        bool hasTaste;
        int category;
        QVector<APIPersonalizedItemData> result;

        bool operator==(const APIPersonalizedData& other) const;
        bool operator!=(const APIPersonalizedData& other) const;

        static APIPersonalizedData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API
