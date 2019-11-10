#pragma once

#include <QVector>
#include "../../util/json.h"
#include "song_privilege.h"

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;

    struct APIPersonalizedNewSongResultSongAlbumData {
        int id;
        QString type;
        QString name;
        QString picUrl;
        QVector<QString> alias;

        static APIPersonalizedNewSongResultSongAlbumData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("type"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("name"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("picUrl"))),
            Util::fromJsonArray<QString>(object.value(QLatin1Literal("alias"))),
          };
        }
    };

    struct APIPersonalizedNewSongResultSongArtistData {
        int id;
        QString name;
        QVector<QString> alias;

        static APIPersonalizedNewSongResultSongArtistData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("name"))),
            Util::fromJsonArray<QString>(object.value(QLatin1Literal("alias"))),
          };
        }
    };

    struct APIPersonalizedNewSongResultSongData {
        int id;
        QString name;
        QVector<QString> alias;
        int mvid;
        QVector<APIPersonalizedNewSongResultSongArtistData> artists;
        APIPersonalizedNewSongResultSongAlbumData album;
        APISongPrivilegeData privilege;

        static APIPersonalizedNewSongResultSongData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("name"))),
            Util::fromJsonArray<QString>(object.value(QLatin1Literal("alias"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("mvid"))),
            Util::fromJsonArray<APIPersonalizedNewSongResultSongArtistData>(object.value(QLatin1Literal("artists"))),
            Util::fromJsonValue<APIPersonalizedNewSongResultSongAlbumData>(object.value(QLatin1Literal("album"))),
            Util::fromJsonValue<APISongPrivilegeData>(object.value(QLatin1Literal("privilege"))),
          };
        }
    };

    struct APIPersonalizedNewSongResultData {
        int id;
        int type;
        QString name;
        APIPersonalizedNewSongResultSongData song;

        static APIPersonalizedNewSongResultData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("type"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("name"))),
            Util::fromJsonValue<APIPersonalizedNewSongResultSongData>(object.value(QLatin1Literal("song"))),
          };
        }
    };

    struct APIPersonalizedNewSongData {
        int category;
        QVector<APIPersonalizedNewSongResultData> result;

        static APIPersonalizedNewSongData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("category"))),
            Util::fromJsonArray<APIPersonalizedNewSongResultData>(object.value(QLatin1Literal("result"))),
          };
        }
    };
}