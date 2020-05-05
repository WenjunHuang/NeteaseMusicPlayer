//
// Created by HUANG WEN JUN on 2019/11/13.
//
#pragma once
#include <QtCore>

namespace MusicPlayer::API {
    struct APIPlaylistCatListItemData {
        QString name;
        int resourceCount;
        int imgId;
        int type;
        int category;
        int resourceType;
        bool hot;
        bool activity;

        bool operator==(const APIPlaylistCatListItemData& second) const;
        bool operator!=(const APIPlaylistCatListItemData& second) const;

        static APIPlaylistCatListItemData fromJsonValue(const QJsonValue& json);
    };

    struct APIPlaylistCatListData {
        APIPlaylistCatListItemData all;
        QVector<APIPlaylistCatListItemData> sub; // APIPlaylistCatListItemData
        QHash<int,QString> categories; // int->QString

        bool operator==(const APIPlaylistCatListData& second) const;
        bool operator!=(const APIPlaylistCatListData& other) const;

        static APIPlaylistCatListData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API
