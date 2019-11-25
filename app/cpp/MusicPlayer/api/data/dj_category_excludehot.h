//
// Created by rick on 2019/11/9.
//

#pragma once

#include "../../util/json.h"
#include <QJsonValue>
#include <QJsonObject>

namespace MusicPlayer::API {
    struct APIDJCategoryItemData {
        Q_GADGET
        Q_PROPERTY(int id MEMBER id)
        Q_PROPERTY(QString name MEMBER name)
      public:
        int id;
        QString name;

        bool operator==(const APIDJCategoryItemData& other);
        bool operator!=(const APIDJCategoryItemData& other);

        static APIDJCategoryItemData fromJsonValue(const QJsonValue &json);
    };

    struct APIDJCategoryExcludeHotData {
        Q_GADGET
        Q_PROPERTY(QVariantList data MEMBER data)
      public:
        QVariantList data;

        bool operator==(const APIDJCategoryExcludeHotData& other);
        bool operator!=(const APIDJCategoryExcludeHotData& other);

        static APIDJCategoryExcludeHotData fromJsonValue(const QJsonValue &json);
    };
}