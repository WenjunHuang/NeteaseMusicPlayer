//
// Created by HUANG WEN JUN on 2019/11/25.
//
#include "banner.h"
namespace MusicPlayer::API{
    APIBannerData APIBannerData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<QUrl>(object.value(QLatin1Literal("imageUrl"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("targetId"))),
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
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("scm"))),
        };
    }
    APIBannersData APIBannersData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();

        return {
            Util::jsonArrayToVariantList<APIBannerData>(object.value(QLatin1Literal("banners")))
        };
    }
}
