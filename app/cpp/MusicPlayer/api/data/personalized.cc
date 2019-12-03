//
// Created by HUANG WEN JUN on 2019/11/26.
//

#include "personalized.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    APIPersonalizedItemData APIPersonalizedItemData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("type"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("name"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("copywriter"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("picUrl"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("canDislike"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("trackNumberUpdateTime"))),
            Util::fromJsonValue<double>(object.value(QLatin1Literal("playCount"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("trackCount"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("highQuality"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("alg"))),
        };
    }

    bool APIPersonalizedItemData::operator==(const APIPersonalizedItemData& other) const {
        return id == other.id && type == other.type && name == other.name && copywriter == other.copywriter &&
               picUrl == other.picUrl && canDislike == other.canDislike &&
               trackNumberUpdateTime == other.trackNumberUpdateTime && playCount == other.playCount &&
               trackCount == other.trackCount && highQuality == other.highQuality && alg == other.alg;
    }

    bool APIPersonalizedItemData::operator!=(const APIPersonalizedItemData& other) const { return !operator==(other); }

    APIPersonalizedData APIPersonalizedData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("hasTaste"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("category"))),
            Util::fromJsonArray<APIPersonalizedItemData>(object.value(QLatin1Literal("result"))),
        };
    }

    bool APIPersonalizedData::operator==(const APIPersonalizedData& other) const {
        return hasTaste == other.hasTaste && category == other.category;
    }

    bool APIPersonalizedData::operator!=(const APIPersonalizedData& other) const { return !operator==(other); }
} // namespace MusicPlayer::API
