#pragma once

#include "song_privilege.h"
#include <QtCore>

namespace MusicPlayer::API {
    struct APIPersonalizedNewSongResultSongAlbumData {
        int id;
        QString type;
        QString name;
        QUrl picUrl;
        QVector<QString> alias;

        bool operator==(const APIPersonalizedNewSongResultSongAlbumData& other) const;
        bool operator!=(const APIPersonalizedNewSongResultSongAlbumData& other) const;

        static APIPersonalizedNewSongResultSongAlbumData fromJsonValue(const QJsonValue& json);
    };

    struct APIPersonalizedNewSongResultSongArtistData {
        int id;
        QString name;
        QVector<QString> alias;

        bool operator==(const APIPersonalizedNewSongResultSongArtistData& other) const;
        bool operator!=(const APIPersonalizedNewSongResultSongArtistData& other) const;

        static APIPersonalizedNewSongResultSongArtistData fromJsonValue(const QJsonValue& json);
    };

    struct APIPersonalizedNewSongResultSongData {
        int id;
        QString name;
        QVector<QString> alias;
        int mvid;
        QVector<APIPersonalizedNewSongResultSongArtistData> artists;
        APIPersonalizedNewSongResultSongAlbumData album;
        APISongPrivilegeData privilege;

        bool operator==(const APIPersonalizedNewSongResultSongData& other) const;
        bool operator!=(const APIPersonalizedNewSongResultSongData& other) const;

        static APIPersonalizedNewSongResultSongData fromJsonValue(const QJsonValue& json);
    };

    struct APIPersonalizedNewSongResultData {
        int id;
        int type;
        QString name;
        APIPersonalizedNewSongResultSongData song;

        bool operator==(const APIPersonalizedNewSongResultData& other) const;

        bool operator!=(const APIPersonalizedNewSongResultData& other) const;

        static APIPersonalizedNewSongResultData fromJsonValue(const QJsonValue& json);
    };

    struct APIPersonalizedNewSongData {
        int category;
        QVector<APIPersonalizedNewSongResultData> result;

        bool operator==(const APIPersonalizedNewSongData& other) const;

        bool operator!=(const APIPersonalizedNewSongData& other) const;

        static APIPersonalizedNewSongData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API
