//
// Created by HUANG WEN JUN on 2019/11/25.
//
#include "banner.h"
#include "../../util/json.h"
namespace MusicPlayer::API {
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
    bool APIBannerData::operator==(const APIBannerData& other) {
        return imageUrl == other.imageUrl && targetId == other.targetId &&
               targetType == other.targetType &&
               titleColor == other.titleColor && typeTitle == other.typeTitle &&
               exclusive == other.exclusive && encodeId == other.encodeId &&
               scm == other.scm;
    }
    bool APIBannerData::operator!=(const APIBannerData& other) {
        return !operator==(other);
    }
    APIBannersData APIBannersData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();

        return {Util::jsonArrayToVariantList<APIBannerData>(
            object.value(QLatin1Literal("banners")))};
    }
    bool APIBannersData::operator==(const APIBannersData& other) {
        return banners == other.banners;
    }
    bool APIBannersData::operator!=(const APIBannersData& other) {
        return !((*this) == other);
    }
} // namespace MusicPlayer::API
