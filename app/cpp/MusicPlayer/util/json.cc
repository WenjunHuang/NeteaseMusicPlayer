//
// Created by rick on 2019/11/9.
//
#include <QtCore/QString>
#include <QtCore/QJsonValue>
#include <QUrl>
#include "json.h"

namespace MusicPlayer::Util {
    template<>
    QString fromJsonValue(const QJsonValue &value) {
      return value.toString();
    }

    template<>
    int fromJsonValue(const QJsonValue &value) {
      return value.toInt();
    }

    template<>
    long fromJsonValue(const QJsonValue &value) {
        return static_cast<long>(value.toDouble());
    }

    template<> QUrl fromJsonValue(const QJsonValue& value) {
        return QUrl(value.toString());
    }

    template<>
    double fromJsonValue(const QJsonValue& value) {
      return value.toDouble();
    }

    template<>
    bool fromJsonValue(const QJsonValue &value) {
      return value.toBool();
    }
}