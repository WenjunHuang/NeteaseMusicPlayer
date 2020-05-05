//
// Created by rick on 2019/11/7.
//
#pragma once
#include <QtCore>
#include <optional>
#include <variant>

namespace MusicPlayer::API {

    struct ErrorResponseError {
        int code;
        std::optional<QString> message;

        static ErrorResponseError fromJsonValue(const QJsonValue& value);
    };

    struct NetworkError {
        QString message;
    };

    struct JsonFormatError {
        QJsonParseError parseError;
    };

    using APIError =
        std::variant<ErrorResponseError, NetworkError, JsonFormatError>;

    QString apiErrorMessage(const APIError& error);
} // namespace MusicPlayer::API
