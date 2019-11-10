#pragma once

#include <QString>
#include <QVector>
#include "../../util/json.h"

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;

    struct APIPersonalizedItemData {
        int id;
        int type;
        QString name;
        QString copywriter;
        QString picUrl;
        bool canDislike;
        int trackNumberUpdateTime;
        double playCount;
        int trackCount;
        bool highQuality;
        QString alg;

        static APIPersonalizedItemData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("type"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("name"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("copywriter"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("picUrl"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("canDislike"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("trackNumberUpdateTime"))),
            Util::fromJsonValue<double>(object.value(QLatin1Literal("playCount"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("trackCount"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("highQuality"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("alg"))),
          };
        }
    };

    struct APIPersonalizedData {
        bool hasTaste;
        int category;
        QVector<APIPersonalizedItemData> result;

        static APIPersonalizedData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("hasTaste"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("category"))),
            Util::fromJsonArray<APIPersonalizedItemData>(object.value(QLatin1Literal("result"))),
          };
        }

    };
}