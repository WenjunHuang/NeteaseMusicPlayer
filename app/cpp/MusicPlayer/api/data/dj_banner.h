#pragma once

#include <QtCore>

namespace MusicPlayer::API {

    struct APIDJBannerData {
        Q_GADGET
        Q_PROPERTY(int targetId MEMBER targetId)
        Q_PROPERTY(int targetType MEMBER targetType)
        Q_PROPERTY(QString pic MEMBER pic)
        Q_PROPERTY(QUrl url MEMBER url)
        Q_PROPERTY(QString typeTitle MEMBER typeTitle)
        Q_PROPERTY(bool exclusive MEMBER exclusive)

      public:
        int targetId;
        int targetType;
        QString pic;
        QUrl url;
        QString typeTitle;
        bool exclusive;

        bool operator==(const APIDJBannerData& other) const;
        bool operator!=(const APIDJBannerData& other) const;

        static APIDJBannerData fromJsonValue(const QJsonValue& value);
    };

    struct APIDJBannersData {
        Q_GADGET
        Q_PROPERTY(QVariantList data MEMBER data)
      public:
        QVariantList data;

        bool operator==(const APIDJBannersData& other) const;

        bool operator!=(const APIDJBannersData& other) const;

        static APIDJBannersData fromJsonValue(const QJsonValue& value);
    };
}
Q_DECLARE_METATYPE(MusicPlayer::API::APIDJBannerData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIDJBannersData)
