//
// Created by HUANG WEN JUN on 2019/11/30.
//

#include "playlist_detail.h"
namespace MusicPlayer::API {
    APIPlayList APIPlayList::fromJsonValue(const QJsonValue& jsonValue) {
        auto obj = jsonValue.toObject();

        return {
            Util::fromJsonValue<int>(obj.value(QLatin1String("id"))),
            Util::fromJsonValue<QString>(obj.value(QLatin1String("name"))),
            Util::fromJsonValue<int>(obj.value(QLatin1String("status"))),
            Util::fromJsonArray<APIPlayListDetailUser>(obj.value(QLatin1String("subscribers"))),
            Util::fromJsonValue<APIPlayListDetailUser>(obj.value(QLatin1String("creator"))),
            Util::fromJsonArray<APIPlayListTrackId>(obj.value(QLatin1String("trackIds"))),
            Util::fromJsonArray<APIPlayListTrack>(obj.value(QLatin1String("tracks"))),
            Util::fromJsonValue<int>(obj.value(QLatin1String("subscribedCount"))),
            Util::fromJsonValue<long>(obj.value(QLatin1String("createTime"))),
            Util::fromJsonValue<bool>(obj.value(QLatin1String("highQuality"))),
            Util::fromJsonValue<int>(obj.value(QLatin1String("userId"))),
            Util::fromJsonValue<long>(obj.value(QLatin1String("updateTime"))),
            Util::fromJsonValue<QUrl>(obj.value(QLatin1String("coverImgUrl"))),
            Util::fromJsonValue<int>(obj.value(QLatin1String("trackCount"))),
            Util::fromJsonValue<QString>(obj.value(QLatin1String("commentThreadId"))),
            Util::fromJsonValue<int>(obj.value(QLatin1String("playCount"))),
            Util::fromJsonArray<QString>(obj.value(QLatin1String("tags"))),
            Util::fromJsonValue<QString>(obj.value(QLatin1String("description"))),
            Util::fromJsonValue<int>(obj.value(QLatin1String("shareCount"))),
            Util::fromJsonValue<int>(obj.value(QLatin1String("commentCount"))),
        };
    }
    APIPlayListDetailData APIPlayListDetailData::fromJsonValue(const QJsonValue& jsonValue) {
        auto obj = jsonValue.toObject();

        return {
            Util::fromJsonValue<APIPlayList>(obj.value(QLatin1String("playlist")))
        };
    }
    APIPlayListDetailUser APIPlayListDetailUser::fromJsonValue(const QJsonValue& jsonValue) {
        auto obj = jsonValue.toObject();

        return {
            Util::fromJsonValue<QUrl>(obj.value(QLatin1String("avatarUrl"))),
            Util::fromJsonValue<QUrl>(obj.value(QLatin1String("backgroundUrl"))),
            Util::fromJsonValue<int>(obj.value(QLatin1String("gender"))),
            Util::fromJsonValue<int>(obj.value(QLatin1String("userId"))),
            Util::fromJsonValue<int>(obj.value(QLatin1String("userType"))),
            Util::fromJsonValue<QString>(obj.value(QLatin1String("nickname"))),
            Util::fromJsonValue<QString>(obj.value(QLatin1String("signature"))),
            Util::fromJsonValue<QString>(obj.value(QLatin1String("description"))),
            Util::fromJsonValue<QString>(obj.value(QLatin1String("detailDescription"))),
            Util::fromJsonArray<QString>(obj.value(QLatin1String("expertTags"))),
            Util::fromJsonValue<int>(obj.value(QLatin1String("vipType"))),
        };
    }
    APIPlayListTrackId APIPlayListTrackId::fromJsonValue(const QJsonValue& jsonValue) {
        auto obj = jsonValue.toObject();

        return {
            Util::fromJsonValue<int>(obj.value(QLatin1String("id"))),
            Util::fromJsonValue<int>(obj.value(QLatin1String("v"))),
        };
    }
    APIPlayListTrack APIPlayListTrack::fromJsonValue(const QJsonValue& jsonValue) {
        auto obj = jsonValue.toObject();
        return {
            Util::fromJsonValue<int>(obj.value(QLatin1String("id"))),
            Util::fromJsonValue<QString>(obj.value(QLatin1String("name"))),
            Util::fromJsonArray<QString>(obj.value(QLatin1String("alia"))),
            Util::fromJsonValue<APIPlayListTrackArtist>(obj.value(QLatin1String("ar"))),
            Util::fromJsonValue<APIPlayListTrackAlbum>(obj.value(QLatin1String("al"))),
            Util::fromJsonValue<int>(obj.value(QLatin1String("dt"))),
        };
    }
    APIPlayListTrackAlbum APIPlayListTrackAlbum::fromJsonValue(const QJsonValue& jsonValue) {
        auto obj = jsonValue.toObject();
        return {
            Util::fromJsonValue<int>(obj.value(QLatin1String("id"))),
            Util::fromJsonValue<QString>(obj.value(QLatin1String("name"))),
            Util::fromJsonValue<QUrl>(obj.value(QLatin1String("picUrl"))),
            Util::fromJsonArray<QString>(obj.value(QLatin1String("tns"))),
            Util::fromJsonValue<long>(obj.value(QLatin1String("pic"))),
        };
    }
    APIPlayListTrackArtist APIPlayListTrackArtist::fromJsonValue(const QJsonValue& jsonValue) {
        auto obj = jsonValue.toObject();
        return {
            Util::fromJsonValue<int>(obj.value(QLatin1String("id"))),
            Util::fromJsonValue<QString>(obj.value(QLatin1String("name"))),
            Util::fromJsonArray<QString>(obj.value(QLatin1String("tns"))),
            Util::fromJsonArray<QString>(obj.value(QLatin1String("alias"))),
        };
    }
}
