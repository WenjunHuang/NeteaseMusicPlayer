//
// Created by HUANG WEN JUN on 2019/12/23.
//

#pragma once
#include <QtCore>
#include "../../util/util.h"

namespace MusicPlayer::API {
    struct APISongUrlDataItem {
        int id;
        QString url;
        int size;
        QString md5;
        QString type;
        int br;

        static APISongUrlDataItem fromJsonValue(const QJsonValue& json);

    };
    struct APISongUrlData {
        QVector<APISongUrlDataItem> data;

        static APISongUrlData fromJsonValue(const QJsonValue& json);
    };
}
