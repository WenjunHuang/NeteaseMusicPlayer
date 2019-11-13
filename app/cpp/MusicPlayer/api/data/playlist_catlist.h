//
// Created by HUANG WEN JUN on 2019/11/13.
//
#pragma once
#include "../../util/json.h"
#include <QtCore>

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;
    struct APIPlaylistCatListItemData {
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

    struct APIPlaylistCatListData {
        APIPlaylistCatListItemData all;
        QVector<APIPlaylistCatListItemData> sub;
        QVariantHash categories;

        static APIPlaylistCatListData fromJsonValue(const QJsonValue& json) {
            auto object = json.toObject();
            return {
                Util::fromJsonValue<APIPlaylistCatListItemData>(
                    object.value(QLatin1Literal("all"))),
                Util::fromJsonArray<APIPlaylistCatListItemData>(
                    object.value(QLatin1Literal("sub"))),
                object.value(QLatin1Literal("categories"))
                    .toObject()
                    .toVariantHash(),
            };
        }
    };
} // namespace MusicPlayer::API
