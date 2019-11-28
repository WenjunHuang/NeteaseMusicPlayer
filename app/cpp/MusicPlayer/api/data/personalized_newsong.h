#pragma once

#include "song_privilege.h"
#include <QtCore>

namespace MusicPlayer::API {
    struct APIPersonalizedNewSongResultSongAlbumData {
        Q_GADGET
        Q_PROPERTY(int id MEMBER id)
        Q_PROPERTY(QString type MEMBER type)
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(QUrl picUrl MEMBER picUrl)
        Q_PROPERTY(QVector<QString> alias MEMBER alias)

      public:
        int id;
        QString type;
        QString name;
        QUrl picUrl;
        QVector<QString> alias;

        bool operator==(const APIPersonalizedNewSongResultSongAlbumData& other) const;
        bool operator!=(const APIPersonalizedNewSongResultSongAlbumData& other) const;

        static APIPersonalizedNewSongResultSongAlbumData
        fromJsonValue(const QJsonValue& json);
    };

    struct APIPersonalizedNewSongResultSongArtistData {
        Q_GADGET
        Q_PROPERTY(int id MEMBER id)
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(QVector<QString> alias MEMBER alias)
      public:
        int id;
        QString name;
        QVector<QString> alias;

        bool operator==(const APIPersonalizedNewSongResultSongArtistData& other) const;
        bool operator!=(const APIPersonalizedNewSongResultSongArtistData& other) const;

        static APIPersonalizedNewSongResultSongArtistData
        fromJsonValue(const QJsonValue& json);
    };

    struct APIPersonalizedNewSongResultSongData {
        Q_GADGET
        Q_PROPERTY(int id MEMBER id)
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(QVector<QString> alias MEMBER alias)
        Q_PROPERTY(int mvid MEMBER mvid)
        Q_PROPERTY(QVariantList artists MEMBER artists)
        Q_PROPERTY(APIPersonalizedNewSongResultSongAlbumData album MEMBER album)
        Q_PROPERTY(APISongPrivilegeData privilege MEMBER privilege)
      public:
        int id;
        QString name;
        QVector<QString> alias;
        int mvid;
        QVariantList artists;
        APIPersonalizedNewSongResultSongAlbumData album;
        APISongPrivilegeData privilege;

        bool operator==(const APIPersonalizedNewSongResultSongData& other) const;
        bool operator!=(const APIPersonalizedNewSongResultSongData& other) const;

        static APIPersonalizedNewSongResultSongData
        fromJsonValue(const QJsonValue& json);
    };

    struct APIPersonalizedNewSongResultData {
        Q_GADGET
        Q_PROPERTY(int id MEMBER id)
        Q_PROPERTY(int type MEMBER type)
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(APIPersonalizedNewSongResultSongData song MEMBER song)
      public:
        int id;
        int type;
        QString name;
        APIPersonalizedNewSongResultSongData song;

        bool operator==(const APIPersonalizedNewSongResultData& other) const;

        bool operator!=(const APIPersonalizedNewSongResultData& other) const;

        static APIPersonalizedNewSongResultData fromJsonValue(const QJsonValue& json);
    };

    struct APIPersonalizedNewSongData {
        Q_GADGET
        Q_PROPERTY(int category MEMBER category)
        Q_PROPERTY(QVariantList result MEMBER result)
      public:
        int category;
        QVariantList result;

        bool operator==(const APIPersonalizedNewSongData& other) const;

        bool operator!=(const APIPersonalizedNewSongData& other) const;

        static APIPersonalizedNewSongData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API

Q_DECLARE_METATYPE(MusicPlayer::API::APIPersonalizedNewSongResultSongAlbumData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIPersonalizedNewSongResultSongArtistData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIPersonalizedNewSongResultSongData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIPersonalizedNewSongResultData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIPersonalizedNewSongData)
