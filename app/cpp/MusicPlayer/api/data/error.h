//
// Created by rick on 2019/11/7.
//
#pragma once
#include "json.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QtCore/QJsonParseError>
#include <optional>
#include <variant>

namespace MusicPlayer::API {
    struct APIError {
        int code;
        std::optional<QString> message;

        static APIError fromJsonValue(const QJsonValue& value) {
            auto object = value.toObject();

            return {MusicPlayer::fromJsonValue<int>(
                        object.value(QLatin1Literal("code"))),
                    MusicPlayer::fromOptionalJsonValue<QString>(
                        QLatin1Literal("message"))};
        }
    };

    struct NetworkError {};

    struct JsonFormatError {
        QJsonParseError parseError;
    };

    using Error = std::variant<APIError, NetworkError, JsonFormatError>;
} // namespace MusicPlayer::API
