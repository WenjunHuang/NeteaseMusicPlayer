
#pragma once

#include "../../util/json.h"
#include <QJsonObject>
#include <QString>
#include <QtCore/QJsonValue>

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;

    struct APIDJBannerData {
        int targetId;
        int targetType;
        QString pic;
        QString url;
        QString typeTitle;
        bool exclusive;

        static APIDJBannerData fromJsonValue(const QJsonValue &value) {
          auto object = value.toObject();

          return {
            Util::fromJsonValue<int>(
              object.value(QLatin1Literal("targetId"))),
            Util::fromJsonValue<int>(
              object.value(QLatin1Literal("targetType"))),
            Util::fromJsonValue<QString>(
              object.value(QLatin1Literal("pic"))),
            Util::fromJsonValue<QString>(
              object.value(QLatin1Literal("url"))),
            Util::fromJsonValue<QString>(
              object.value(QLatin1Literal("typeTitle"))),
            Util::fromJsonValue<bool>(
              object.value(QLatin1Literal("exclusive")))
          };
        }
    };

    struct APIDJBannersData {
        QVector<APIDJBannerData> data;

        static APIDJBannersData fromJsonValue(const QJsonValue &value) {
          auto object = value.toObject();
          return {
            Util::fromJsonArray<APIDJBannerData>(object.value(QLatin1Literal("data")))
          };

        }
    };
}