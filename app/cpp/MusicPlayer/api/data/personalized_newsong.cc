//
// Created by HUANG WEN JUN on 2019/11/26.
//
#include "personalized_newsong.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    APIPersonalizedNewSongResultSongAlbumData APIPersonalizedNewSongResultSongAlbumData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("type"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("name"))),
            Util::fromJsonValue<QUrl>(object.value(QLatin1Literal("picUrl"))),
            Util::fromJsonArray<QString>(object.value(QLatin1Literal("alias"))),
        };
    }

    bool APIPersonalizedNewSongResultSongAlbumData::operator==(const APIPersonalizedNewSongResultSongAlbumData& other) const {
        return id == other.id && type == other.type && name == other.name && picUrl == other.picUrl && alias == other.alias;
    }

    bool APIPersonalizedNewSongResultSongAlbumData::operator!=(const APIPersonalizedNewSongResultSongAlbumData& other) const {
        return !operator==(other);
    }

    APIPersonalizedNewSongResultSongArtistData
    APIPersonalizedNewSongResultSongArtistData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("name"))),
            Util::fromJsonArray<QString>(object.value(QLatin1Literal("alias"))),
        };
    }

    bool APIPersonalizedNewSongResultSongArtistData::operator==(const APIPersonalizedNewSongResultSongArtistData& other) const {
        return id == other.id && name == other.name && alias == other.alias;
    }

    bool APIPersonalizedNewSongResultSongArtistData::operator!=(const APIPersonalizedNewSongResultSongArtistData& other) const {
        return !operator==(other);
    }

    APIPersonalizedNewSongResultSongData APIPersonalizedNewSongResultSongData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("name"))),
            Util::fromJsonArray<QString>(object.value(QLatin1Literal("alias"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("mvid"))),
            Util::jsonArrayToVariantList<APIPersonalizedNewSongResultSongArtistData>(object.value(QLatin1Literal("artists"))),
            Util::fromJsonValue<APIPersonalizedNewSongResultSongAlbumData>(object.value(QLatin1Literal("album"))),
            Util::fromJsonValue<APISongPrivilegeData>(object.value(QLatin1Literal("privilege"))),
        };
    }
    bool APIPersonalizedNewSongResultSongData::operator==(const APIPersonalizedNewSongResultSongData& other) const {
        return id == other.id && name == other.name && alias == other.alias && mvid == other.mvid && artists == other.artists &&
               album == other.album && privilege == other.privilege;
    }
    bool APIPersonalizedNewSongResultSongData::operator!=(const APIPersonalizedNewSongResultSongData& other) const {
        return !operator==(other);
    }

    APIPersonalizedNewSongData APIPersonalizedNewSongData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("category"))),
            Util::jsonArrayToVariantList<APIPersonalizedNewSongResultData>(object.value(QLatin1Literal("result"))),
        };
    }

    bool APIPersonalizedNewSongData::operator==(const APIPersonalizedNewSongData& other) const {
        return category == other.category && result == other.result;
    }

    bool APIPersonalizedNewSongData::operator!=(const APIPersonalizedNewSongData& other) const { return !operator==(other); }

    APIPersonalizedNewSongResultData APIPersonalizedNewSongResultData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("type"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("name"))),
            Util::fromJsonValue<APIPersonalizedNewSongResultSongData>(object.value(QLatin1Literal("song"))),
        };
    }

    bool APIPersonalizedNewSongResultData::operator==(const APIPersonalizedNewSongResultData& other) const {
        return id == other.id && type == other.type && name == other.name && song == other.song;
    }

    bool APIPersonalizedNewSongResultData::operator!=(const APIPersonalizedNewSongResultData& other) const {
        return !operator==(other);
    }
} // namespace MusicPlayer::API
