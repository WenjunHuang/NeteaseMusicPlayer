//
// Created by rick on 2019/11/25.
//
#include "error.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    ErrorResponseError ErrorResponseError::fromJsonValue(const QJsonValue& value) {
        auto object = value.toObject();

        return {Util::fromJsonValue<int>(object.value(QLatin1Literal("code"))),
                Util::fromOptionalJsonValue<QString>(QLatin1Literal("message"))};
    }
    QString apiErrorMessage(const APIError& error) {
        return std::visit(
            [](const auto& e) -> QString {
                if constexpr (std::is_convertible_v<decltype(e), ErrorResponseError>)
                    return e.message.value_or(QString(""));
                else if constexpr (std::is_convertible_v<decltype(e), NetworkError>)
                    return e.message;
                else if constexpr (std::is_convertible_v<decltype(e), JsonFormatError>) {
                    return e.parseError.errorString();
                }
            },
            error);
    }
} // namespace MusicPlayer::API
