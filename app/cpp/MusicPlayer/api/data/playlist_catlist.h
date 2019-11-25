//
// Created by HUANG WEN JUN on 2019/11/13.
//
#pragma once
#include "../../util/json.h"
#include <QtCore>

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;

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

        static APIPlaylistCatListItemData
        fromJsonValue(const QJsonValue& json) {
            auto object = json.toObject();
            return {
                Util::fromJsonValue<QString>(
                    object.value(QLatin1Literal("name"))),
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("resourceCount"))),
                Util::fromJsonValue<int>(object.value(QLatin1Literal("imgId"))),
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("category"))),
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("resourceType"))),
                Util::fromJsonValue<bool>(object.value(QLatin1Literal("hot"))),
                Util::fromJsonValue<bool>(
                    object.value(QLatin1Literal("activity"))),
            };
        }
    };

    inline bool operator==(const APIPlaylistCatListItemData& first,
                    const APIPlaylistCatListItemData& second) {
        return first.name == second.name &&
               first.resourceCount == second.resourceCount &&
               first.imgId == second.imgId && first.type == second.type &&
               first.category == second.category &&
               first.resourceType == second.resourceType &&
               first.hot == second.hot && first.activity == second.activity;
    }

    inline bool operator!=(const APIPlaylistCatListItemData& first,
                    const APIPlaylistCatListItemData& second) {
        return !(first == second);
    }

    struct APIPlaylistCatListData {
        Q_GADGET
        Q_PROPERTY(APIPlaylistCatListItemData all MEMBER all)
        Q_PROPERTY(QVariantHash categories MEMBER categories)
        Q_PROPERTY(QVariantList sub MEMBER sub)
      public:
        APIPlaylistCatListItemData all;
        QVariantList sub;
        QVariantHash categories;
        //        QVector<APIPlaylistCatListItemData> sub;

        static APIPlaylistCatListData fromJsonValue(const QJsonValue& json) {
            auto object = json.toObject();
            return {
                Util::fromJsonValue<APIPlaylistCatListItemData>(
                    object.value(QLatin1Literal("all"))),
                Util::jsonArrayToVariantList<APIPlaylistCatListItemData>(
                    object.value(QLatin1Literal("sub"))),
                object.value(QLatin1Literal("categories"))
                    .toObject()
                    .toVariantHash(),
            };
        }
    };

    inline bool operator==(const APIPlaylistCatListData& first,const APIPlaylistCatListData& second) {
        return first.all == second.all && first.sub == second.sub && first.categories == second.categories;
    }
} // namespace MusicPlayer::API
Q_DECLARE_METATYPE(MusicPlayer::API::APIPlaylistCatListItemData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIPlaylistCatListData)
