//
// Created by HUANG WEN JUN on 2019/11/25.
//
#include "banner.h"
#include "../../util/json.h"
namespace MusicPlayer::API {
    APIBannerData APIBannerData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<QString>(object.value(QLatin1String("imageUrl"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("targetId"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("targetType"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("titleColor"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("typeTitle"))),
            Util::fromJsonValue<bool>(object.value(QLatin1String("exclusive"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("encodeId"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("scm"))),
        };
    }

    bool APIBannerData::operator==(const APIBannerData& other) const {
        return imageUrl == other.imageUrl && targetId == other.targetId && targetType == other.targetType &&
               titleColor == other.titleColor && typeTitle == other.typeTitle && exclusive == other.exclusive &&
               encodeId == other.encodeId && scm == other.scm;
    }

    bool APIBannerData::operator!=(const APIBannerData& other) const { return !operator==(other); }

    APIBannersData APIBannersData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();

        return {Util::fromJsonArray<APIBannerData>(object.value(QLatin1String("banners")))};
    }

    bool APIBannersData::operator==(const APIBannersData& other) const { return banners == other.banners; }

    bool APIBannersData::operator!=(const APIBannersData& other) const { return !operator==(other); }
} // namespace MusicPlayer::API
