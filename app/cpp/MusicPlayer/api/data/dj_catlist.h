//
// Created by HUANG WEN JUN on 2019/12/8.
//
#pragma once
#include "../../util/util.h"
#include <QtCore>
namespace MusicPlayer::API {

    struct APIDJCategoryItemData {
        int id;
        QString picPCWhiteUrl;
        QString name;

        static APIDJCategoryItemData fromJsonValue(const QJsonValue& jsonValue);
    };

    struct APIDJCategoryListData {
        QVector<APIDJCategoryItemData> categories;

        static APIDJCategoryListData fromJsonValue(const QJsonValue& jsonValue);
    };
} // namespace MusicPlayer::API
