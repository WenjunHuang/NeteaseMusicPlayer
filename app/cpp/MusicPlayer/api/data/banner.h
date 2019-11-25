#pragma once

#include "../../util/json.h"
#include <QtCore/QMetaType>
#include <QtCore/QVector>
#include <QtCore/qobjectdefs.h>

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;

    struct APIBannerData {

        Q_GADGET
        Q_PROPERTY(QString imageUrl MEMBER imageUrl)
      public:
        QString imageUrl;
        int targetId;
        int targetType;
        QString titleColor;
        QString typeTitle;
        bool exclusive;
        QString encodeId;
        QString scm;

        static APIBannerData fromJsonValue(const QJsonValue& json) {
            auto object = json.toObject();
            return {
                Util::fromJsonValue<QString>(
                    object.value(QLatin1Literal("imageUrl"))),
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("targetId"))),
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("targetType"))),
                Util::fromJsonValue<QString>(
                    object.value(QLatin1Literal("titleColor"))),
                Util::fromJsonValue<QString>(
                    object.value(QLatin1Literal("typeTitle"))),
                Util::fromJsonValue<bool>(
                    object.value(QLatin1Literal("exclusive"))),
                Util::fromJsonValue<QString>(
                    object.value(QLatin1Literal("encodeId"))),
                Util::fromJsonValue<QString>(
                    object.value(QLatin1Literal("scm"))),
            };
        }
    };

    struct APIBannersData {
        Q_GADGET
        Q_PROPERTY(QVector<APIBannerData> banners MEMBER banners)
      public:
        QVector<APIBannerData> banners;

        static APIBannersData fromJsonValue(const QJsonValue& json) {
            auto object = json.toObject();

            return {Util::fromJsonArray<APIBannerData>(
                object.value(QLatin1Literal("banners")))};
        }
    };
} // namespace MusicPlayer::API

Q_DECLARE_METATYPE(MusicPlayer::API::APIBannerData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIBannersData)
