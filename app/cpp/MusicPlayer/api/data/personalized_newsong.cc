//
// Created by HUANG WEN JUN on 2019/11/26.
//
#include "personalized_newsong.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    APIPersonalizedNewSongResultSongAlbumData APIPersonalizedNewSongResultSongAlbumData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1String("id"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("type"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("name"))),
            Util::fromJsonValue<QUrl>(object.value(QLatin1String("picUrl"))),
            Util::fromJsonArray<QString>(object.value(QLatin1String("alias"))),
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
            Util::fromJsonValue<int>(object.value(QLatin1String("id"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("name"))),
            Util::fromJsonArray<QString>(object.value(QLatin1String("alias"))),
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
            Util::fromJsonValue<int>(object.value(QLatin1String("id"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("name"))),
            Util::fromJsonArray<QString>(object.value(QLatin1String("alias"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("mvid"))),
            Util::fromJsonArray<APIPersonalizedNewSongResultSongArtistData>(object.value(QLatin1String("artists"))),
            Util::fromJsonValue<APIPersonalizedNewSongResultSongAlbumData>(object.value(QLatin1String("album"))),
            Util::fromJsonValue<APISongPrivilegeData>(object.value(QLatin1String("privilege"))),
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
            Util::fromJsonValue<int>(object.value(QLatin1String("category"))),
            Util::fromJsonArray<APIPersonalizedNewSongResultData>(object.value(QLatin1String("result"))),
        };
    }

    bool APIPersonalizedNewSongData::operator==(const APIPersonalizedNewSongData& other) const {
        return category == other.category && result == other.result;
    }

    bool APIPersonalizedNewSongData::operator!=(const APIPersonalizedNewSongData& other) const { return !operator==(other); }

    APIPersonalizedNewSongResultData APIPersonalizedNewSongResultData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1String("id"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("type"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("name"))),
            Util::fromJsonValue<APIPersonalizedNewSongResultSongData>(object.value(QLatin1String("song"))),
        };
    }

    bool APIPersonalizedNewSongResultData::operator==(const APIPersonalizedNewSongResultData& other) const {
        return id == other.id && type == other.type && name == other.name && song == other.song;
    }

    bool APIPersonalizedNewSongResultData::operator!=(const APIPersonalizedNewSongResultData& other) const {
        return !operator==(other);
    }
} // namespace MusicPlayer::API
