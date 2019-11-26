#pragma once

#include <QtCore>

namespace MusicPlayer::API {
    struct APIBannerData {
        Q_GADGET
        Q_PROPERTY(QUrl imageUrl MEMBER imageUrl)
        Q_PROPERTY(int targetId MEMBER targetId)
        Q_PROPERTY(int targetType MEMBER targetType)
        Q_PROPERTY(QString titleColor MEMBER titleColor)
        Q_PROPERTY(QString typeTitle MEMBER typeTitle)
        Q_PROPERTY(bool exclusive MEMBER exclusive)
        Q_PROPERTY(QString encodeId MEMBER encodeId)
        Q_PROPERTY(QString scm MEMBER scm)
      public:
        QUrl imageUrl;
        int targetId;
        int targetType;
        QString titleColor;
        QString typeTitle;
        bool exclusive;
        QString encodeId;
        QString scm;

        bool operator==(const APIBannerData& other);

        bool operator!=(const APIBannerData& other);

        static APIBannerData fromJsonValue(const QJsonValue& json);
    };

    struct APIBannersData {
        Q_GADGET
        Q_PROPERTY(QVariantList banners MEMBER banners)
      public:
        QVariantList banners;

        bool operator==(const APIBannersData& other);

        bool operator!=(const APIBannersData& other);

        static APIBannersData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API

Q_DECLARE_METATYPE(MusicPlayer::API::APIBannerData)