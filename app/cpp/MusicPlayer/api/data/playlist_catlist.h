//
// Created by HUANG WEN JUN on 2019/11/13.
//
#pragma once
#include <QtCore>

namespace MusicPlayer::API {
    struct APIPlaylistCatListItemData {
        Q_GADGET
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(int resourceCount MEMBER resourceCount)
        Q_PROPERTY(int imgId MEMBER imgId)
        Q_PROPERTY(int type MEMBER type)
        Q_PROPERTY(int category MEMBER category)
        Q_PROPERTY(int resourceType MEMBER resourceType)
        Q_PROPERTY(bool hot MEMBER hot)
        Q_PROPERTY(bool activity MEMBER activity)
      public:
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
        Q_GADGET
        Q_PROPERTY(APIPlaylistCatListItemData all MEMBER all)
        Q_PROPERTY(QVariantHash categories MEMBER categories)
        Q_PROPERTY(QVariantList sub MEMBER sub)
      public:
        APIPlaylistCatListItemData all;
        QVariantList sub; // APIPlaylistCatListItemData
        QVariantHash categories; // QString->QString

        bool operator==(const APIPlaylistCatListData& second) const;
        bool operator!=(const APIPlaylistCatListData& other) const;

        static APIPlaylistCatListData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API

Q_DECLARE_METATYPE(MusicPlayer::API::APIPlaylistCatListItemData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIPlaylistCatListData)
