//
// Created by rick on 2019/11/7.
//
#pragma once
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <optional>

namespace MusicPlayer::Util {
    template <typename T> T fromJsonValue(const QJsonValue& value) {
        return T::fromJsonValue(value);
    }



    template <> QString fromJsonValue(const QJsonValue& value);

    template <> int fromJsonValue(const QJsonValue& value);

    template<> double fromJsonValue(const QJsonValue& value);


    template<> bool fromJsonValue(const QJsonValue& value);

    template <typename T> QVector<T> fromJsonArray(const QJsonValue& value) {
        auto array = value.toArray();
        QVector<T> result;
        for (const auto& v : array) {
            result.append(fromJsonValue<T>(v));
        }
        return result;
    }

    template <typename T>
    std::optional<T> fromOptionalJsonValue(const QJsonValue& value) {
        if (value.isNull() || value.isUndefined())
            return std::nullopt;
        else {
            return std::make_optional(fromJsonValue<T>(value));
        }
    }
}
