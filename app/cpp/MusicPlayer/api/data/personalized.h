#pragma once

#include <QtCore>

namespace MusicPlayer::API {

    struct APIPersonalizedItemData {
        Q_GADGET
        Q_PROPERTY(int id MEMBER id)
        Q_PROPERTY(int type MEMBER type)
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(QString copywriter MEMBER copywriter)
        Q_PROPERTY(QUrl picUrl MEMBER picUrl)
        Q_PROPERTY(bool canDislike MEMBER canDislike)
        Q_PROPERTY(int trackNumberUpdateTime MEMBER trackNumberUpdateTime)
        Q_PROPERTY(double playCount MEMBER playCount)
        Q_PROPERTY(int trackCount MEMBER trackCount)
        Q_PROPERTY(bool highQuality MEMBER highQuality)
        Q_PROPERTY(QString alg MEMBER alg)
      public:
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
        Q_GADGET
        Q_PROPERTY(bool hasTaste MEMBER hasTaste)
        Q_PROPERTY(int category MEMBER category)
        Q_PROPERTY(QVariantList result MEMBER result)
      public:
        bool hasTaste;
        int category;
        //        QVector<APIPersonalizedItemData> result;
        QVariantList result;

        bool operator==(const APIPersonalizedData& other) const;
        bool operator!=(const APIPersonalizedData& other) const;

        static APIPersonalizedData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API
Q_DECLARE_METATYPE(MusicPlayer::API::APIPersonalizedItemData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIPersonalizedData)
