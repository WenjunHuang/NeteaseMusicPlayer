
#pragma once
#include "json.h"
#include <QJsonObject>
#include <QString>
#include <QtCore/QJsonValue>

namespace MusicPlayer::API {
    struct APIDJBannerData {
        int targetId;
        int targetType;
        QString pic;
        QString url;
        QString typeTitle;
        bool exclusive;

        static APIDJBannerData fromJsonValue(const QJsonValue& value) {
            auto object = value.toObject();

            return {
                MusicPlayer::fromJsonValue<int>(
                    object.value(QLatin1Literal("target_id"))),
                    MusicPlayer::fromJsonValue<int>(
                        object.value(QLatin1Literal("target_type"))),
                    MusicPlayer::fromJsonValue<QString>(
                        object.value(QLatin1Literal("pic"))),
                    MusicPlayer::fromJsonValue<QString>(
                        object.value(QLatin1Literal("url"))),
                    MusicPlayer::fromJsonValue<QString>(
                        object.value(QLatin1Literal("type_title"))),
                    MusicPlayer::fromJsonValue<bool>(
                        object.value(QLatin1Literal("exclusive")))
            };
        }
    };
}