//
// Created by rick on 2019/11/25.
//
#include "error.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    APIError APIError::fromJsonValue(const QJsonValue& value) {
        auto object = value.toObject();

        return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("code"))),
            Util::fromOptionalJsonValue<QString>(QLatin1Literal("message"))};
    }
}
