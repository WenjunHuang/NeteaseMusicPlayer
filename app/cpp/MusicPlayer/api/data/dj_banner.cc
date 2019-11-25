//
// Created by rick on 2019/11/25.
//
#include "dj_banner.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    APIDJBannerData APIDJBannerData::fromJsonValue(const QJsonValue& value) {
        auto object = value.toObject();

        return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("targetId"))),
            Util::fromJsonValue<int>(
                object.value(QLatin1Literal("targetType"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("pic"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("url"))),
            Util::fromJsonValue<QString>(
                object.value(QLatin1Literal("typeTitle"))),
            Util::fromJsonValue<bool>(
                object.value(QLatin1Literal("exclusive")))};
    }

    bool APIDJBannerData::operator==(const APIDJBannerData& other) const {
        return targetId == other.targetId && targetType == other.targetType &&
               pic == other.pic && url == other.url &&
               typeTitle == other.typeTitle && exclusive == other.exclusive;
    }

    bool APIDJBannerData::operator!=(const APIDJBannerData& other) const {
        return !operator==(other);
    }

    APIDJBannersData APIDJBannersData::fromJsonValue(const QJsonValue& value) {
        auto object = value.toObject();
        return {Util::jsonArrayToVariantList<APIDJBannerData>(
            object.value(QLatin1Literal("data")))};
    }

    bool APIDJBannersData::operator==(const APIDJBannersData& other) const {
        return data == other.data;
    }

    bool APIDJBannersData::operator!=(const APIDJBannersData& other) const {
        return !operator==(other);
    }
} // namespace MusicPlayer::API
