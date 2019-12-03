//
// Created by HUANG WEN JUN on 2019/11/30.
//

#include "top_playlist.h"
namespace MusicPlayer::API {
    APITopPlayListItemData APITopPlayListItemData::fromJsonValue(const QJsonValue& jsonValue) {
        auto jsonObject = jsonValue.toObject();

        return {Util::fromJsonValue<int>(jsonObject.value(QLatin1String("id"))),
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
                Util::fromJsonValue<QUrl>(jsonObject.value(QLatin1String("coverImgUrl"))),
                Util::fromJsonValue<APIPlayListDetailUser>(jsonObject.value(QLatin1String("creator"))),
                Util::fromJsonValue<int>(jsonObject.value(QLatin1String("playCount"))),
                    };
    }

    APITopPlayListData APITopPlayListData::fromJsonValue(const QJsonValue& json) {
        auto jsonObject = json.toObject();
        return {Util::fromJsonValue<int>(jsonObject.value(QLatin1String("total"))),
                Util::fromJsonValue<long>(jsonObject.value(QLatin1Literal("lasttime"))),
                Util::fromJsonValue<bool>(jsonObject.value(QLatin1String("more"))),
                Util::fromJsonValue<int>(jsonObject.value(QLatin1String("code"))),
                Util::fromJsonArray<APITopPlayListItemData>(jsonObject.value(QLatin1String("playlists")))};
    }
} // namespace MusicPlayer::API
