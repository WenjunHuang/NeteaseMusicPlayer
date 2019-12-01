//
// Created by HUANG WEN JUN on 2019/11/30.
//

#include "top_playlist_highquality.h"
namespace MusicPlayer::API {
    APITopPlayListItemData APITopPlayListItemData::fromJsonValue(const QJsonValue& jsonValue) {
        auto jsonObject = jsonValue.toObject();

        return {
            Util::fromJsonValue<int>(jsonObject.value(QLatin1String("id"))),
            Util::fromJsonValue<QString>(jsonObject.value(QLatin1String("name"))),
            Util::fromJsonValue<long>(jsonObject.value(QLatin1String("trackNumberUpdateTime"))),
            Util::fromJsonValue<int>(jsonObject.value(QLatin1String("status"))),
            Util::fromJsonValue<int>(jsonObject.value(QLatin1String("userId"))),
            Util::fromJsonValue<long>(jsonObject.value(QLatin1String("createTime"))),
            Util::fromJsonValue<long>(jsonObject.value(QLatin1String("updateTime"))),
            Util::fromJsonValue<int>(jsonObject.value(QLatin1String("subscribedCount"))),
            Util::fromJsonValue<int>(jsonObject.value(QLatin1String("commentCount"))),
            Util::fromJsonValue<QString>(jsonObject.value(QLatin1String("copywriter"))),
            Util::fromJsonValue<QString>(jsonObject.value(QLatin1String("tag"))),
        };
    }

    APITopPlayListHighQualityData APITopPlayListHighQualityData::fromJsonValue(const QJsonValue& json) {
        auto jsonObject = json.toObject();
        return {Util::fromJsonValue<int>(jsonObject.value(QLatin1String("total"))),
                Util::fromJsonValue<long>(jsonObject.value(QLatin1Literal("lasttime"))),
                Util::fromJsonValue<bool>(jsonObject.value(QLatin1String("more"))),
                Util::fromJsonValue<int>(jsonObject.value(QLatin1String("code"))),
                Util::jsonArrayToVariantList<APITopPlayListItemData>(jsonObject.value(QLatin1String("playlists")))};
    }
}
