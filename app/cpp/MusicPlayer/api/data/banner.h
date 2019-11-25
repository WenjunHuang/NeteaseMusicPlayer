#pragma once

#include <QtCore>
#include "../../util/json.h"

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;

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

//        bool operator==(const APIBannerData&other) {
//            return imageUrl == other.imageUrl && targetId == other.targetId && targetType == other.
//        }
        bool operator<=>(const APIBannerData& other) const = default;

        static APIBannerData fromJsonValue(const QJsonValue &json);
    };

    struct APIBannersData {
        Q_GADGET
        Q_PROPERTY(QVariantList banners MEMBER banners)
      public:
        QVariantList banners;

        static APIBannersData fromJsonValue(const QJsonValue &json);
    };
}

Q_DECLARE_METATYPE(MusicPlayer::API::APIBannerData)