//
// Created by HUANG WEN JUN on 2019/11/26.
//

#include "personalized.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    APIPersonalizedItemData APIPersonalizedItemData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1String("id"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("type"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("name"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("copywriter"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("picUrl"))),
            Util::fromJsonValue<bool>(object.value(QLatin1String("canDislike"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("trackNumberUpdateTime"))),
            Util::fromJsonValue<double>(object.value(QLatin1String("playCount"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("trackCount"))),
            Util::fromJsonValue<bool>(object.value(QLatin1String("highQuality"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("alg"))),
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
            Util::fromJsonValue<bool>(object.value(QLatin1String("hasTaste"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("category"))),
            Util::fromJsonArray<APIPersonalizedItemData>(object.value(QLatin1String("result"))),
        };
    }

    bool APIPersonalizedData::operator==(const APIPersonalizedData& other) const {
        return hasTaste == other.hasTaste && category == other.category;
    }

    bool APIPersonalizedData::operator!=(const APIPersonalizedData& other) const { return !operator==(other); }
} // namespace MusicPlayer::API
