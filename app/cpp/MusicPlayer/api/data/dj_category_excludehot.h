//
// Created by rick on 2019/11/9.
//

#pragma once

#include "../../util/json.h"
#include <QJsonValue>
#include <QJsonObject>

namespace MusicPlayer::API {
    struct APIDJCategoryItemData {
        int id;
        QString name;

        static APIDJCategoryItemData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(
              object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<QString>(
              object.value(QLatin1Literal("name")))
          };
        }
    };

    struct APIDJCategoryExcludeHotData {
        QVector<APIDJCategoryItemData> data;

        static APIDJCategoryExcludeHotData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonArray<APIDJCategoryItemData>(object.value(QLatin1Literal("data")))
          };
        }
    };
}