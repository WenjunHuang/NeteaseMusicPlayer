//
// Created by rick on 2019/11/7.
//
#pragma once
#include <QtCore>

namespace MusicPlayer::API {
    class APIErrorKind: public QObject {
        Q_OBJECT
      public:
        enum class Kind {
            ErrorResponseError,
            NetworkError,
            JsonFormatError,
        };
    };
    struct APIError {
        Q_GADGET
        Q_PROPERTY(int code MEMBER code)
        Q_PROPERTY(QVariant message MEMBER message)
      public:
        int code;
        QVariant message;
//        std::optional<QString> message;

        static APIError fromJsonValue(const QJsonValue& value);
    };

    struct NetworkError {
        QString message;
    };

    struct JsonFormatError {
        QJsonParseError parseError;
    };

    using Error = std::variant<APIError, NetworkError, JsonFormatError>;
} // namespace MusicPlayer::MusicAPI
