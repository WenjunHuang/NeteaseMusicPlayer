#pragma once

#include "../../util/json.h"

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;

    struct APIBannerData {
        QString imageUrl;
        int targetId;
        int targetType;
        QString titleColor;
        QString typeTitle;
        bool exclusive;
        QString encodeId;
        QString scm;

        static APIBannerData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("imageUrl"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("targetId"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("targetType"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("titleColor"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("typeTitle"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("exclusive"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("encodeId"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("scm"))),
          };
        }
    };

    struct APIBannersData {
        QVector<APIBannerData> banners;

        static APIBannersData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();

          return {
            Util::fromJsonArray<APIBannerData>(object.value(QLatin1Literal("banners")))
          };
        }
    };
}