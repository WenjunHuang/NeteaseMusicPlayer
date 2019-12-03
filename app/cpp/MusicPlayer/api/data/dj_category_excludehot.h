//
// Created by rick on 2019/11/9.
//

#pragma once

#include <QtCore>

namespace MusicPlayer::API {
    struct APIDJCategoryItemData {
        int id;
        QString name;

        bool operator==(const APIDJCategoryItemData& other) const;
        bool operator!=(const APIDJCategoryItemData& other) const;

        static APIDJCategoryItemData fromJsonValue(const QJsonValue& json);
    };

    struct APIDJCategoryExcludeHotData {
        QVector<APIDJCategoryItemData> data;

        bool operator==(const APIDJCategoryExcludeHotData& other) const;
        bool operator!=(const APIDJCategoryExcludeHotData& other) const;

        static APIDJCategoryExcludeHotData
        fromJsonValue(const QJsonValue& json);
    };
}

