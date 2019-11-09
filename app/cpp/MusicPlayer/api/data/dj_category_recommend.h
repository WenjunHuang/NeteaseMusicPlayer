
#pragma once

#include <QJsonValue>
#include <QJsonObject>
#include <QVector>
#include <optional>
#include "../../util/json.h"

using namespace std;
namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;

    struct APIDJCategoryRecommendItemRadioData {
        int id;
        QString name;
        QString rcmdText;
        int radioFeeType;
        int feeScope;
        QString picUrl;
        int programCount;
        optional<int> playCount;
        QString alg;
        QString lastProgramName;

        static APIDJCategoryRecommendItemRadioData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("name"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("rcmdText"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("radioFeeType"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("feeScope"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("picUrl"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("programCount"))),
            Util::fromOptionalJsonValue<int>(object.value(QLatin1Literal("playCount"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("alg"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("lastProgramName")))
          };
        }
    };

    struct APIDJCategoryRecommendItemData {
        int categoryId;
        QString categoryName;
        QVector<APIDJCategoryRecommendItemRadioData> radios;

        static APIDJCategoryRecommendItemData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("categoryId"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("categoryName"))),
            Util::fromJsonArray<APIDJCategoryRecommendItemRadioData>(object.value(QLatin1Literal("radios"))),
          };
        }
    };

    struct APIDJCategoryRecommendData {
        QVector<APIDJCategoryRecommendItemData> data;

        static APIDJCategoryRecommendData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonArray<APIDJCategoryRecommendItemData>(object.value(QLatin1Literal("data")))
          };
        }
    };
}