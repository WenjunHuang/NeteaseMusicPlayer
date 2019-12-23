//
// Created by HUANG WEN JUN on 2019/12/23.
//

#include "song_url.h"
namespace MusicPlayer::API {
    APISongUrlDataItem APISongUrlDataItem::fromJsonValue(const QJsonValue& json) {
        auto jsonObject = json.toObject();

        return APISongUrlDataItem{
            Util::fromJsonValue<int>(jsonObject.value(QLatin1String("id"))),
            Util::fromJsonValue<QString>(jsonObject.value(QLatin1String("url"))),
            Util::fromJsonValue<int>(jsonObject.value(QLatin1String("size"))),
            Util::fromJsonValue<QString>(jsonObject.value(QLatin1String("md5"))),
            Util::fromJsonValue<QString>(jsonObject.value(QLatin1String("type"))),
            Util::fromJsonValue<int>(jsonObject.value(QLatin1String("br"))),
        };
    }

    APISongUrlData APISongUrlData::fromJsonValue(const QJsonValue& json) {
        auto jsonObject = json.toObject();
        return APISongUrlData{
            Util::fromJsonArray<APISongUrlDataItem>(jsonObject.value(QLatin1String("data"))),
        };
    }
}
