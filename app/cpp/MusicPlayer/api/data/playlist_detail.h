//
// Created by HUANG WEN JUN on 2019/11/30.
//

#pragma once
#include "../../util/json.h"
#include <QtCore>

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;

    struct APIPlayListTrackArtist {
        int id;
        QString name;
        QVector<QString> tns;
        QVector<QString> alias;

        static APIPlayListTrackArtist fromJsonValue(const QJsonValue& jsonValue);
    };

    struct APIPlayListTrackAlbum {
        int id;
        QString name;
        QUrl picUrl;
        QVector<QString> tns;
        long pic;

        static APIPlayListTrackAlbum fromJsonValue(const QJsonValue& jsonValue);
    };

    struct APIPlayListTrack {
        int id;
        QString name;
        QVector<QString> alia;
        APIPlayListTrackArtist ar;
        APIPlayListTrackAlbum al;
        int dt;

        static APIPlayListTrack fromJsonValue(const QJsonValue& jsonValue);
    };

    struct APIPlayListTrackId {
        int id;
        int v;

        static APIPlayListTrackId fromJsonValue(const QJsonValue& jsonValue);
    };

    struct APIPlayListDetailUser {
        QUrl avatarUrl;
        QUrl backgroundUrl;
        int gender;
        int userId;
        int userType;
        QString nickname;
        QString signature;
        QString description;
        QString detailDescription;
        QVector<QString> expertTags;
        int vipType;

        static APIPlayListDetailUser fromJsonValue(const QJsonValue& jsonValue);
    };

    struct APIPlayList {
        int id;
        QString name;
        int status;
        QVector<APIPlayListDetailUser> subscribers; // APIPlayListDetailUser
        APIPlayListDetailUser creator;
        QVector<APIPlayListTrackId> trackIds; // APIPlayListTrackId
        QVector<APIPlayListTrack> tracks;
        int subscribedCount;
        long createTime;
        bool highQuality;
        int userId;
        long updateTime;
        QUrl coverImgUrl;
        int trackCount;
        QString commentThreadId;
        int playCount;
        QVector<QString> tags;
        QString description;
        int shareCount;
        int commentCount;

        static APIPlayList fromJsonValue(const QJsonValue& jsonValue);
    };

    struct APIPlayListDetailData {
        APIPlayList playlist;

        static APIPlayListDetailData fromJsonValue(const QJsonValue& jsonValue);
    };
} // namespace MusicPlayer::API
