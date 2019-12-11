//
// Created by rick on 2019/11/9.
//

#pragma once

#include <QtCore>
#include "dj_catlist.h"

namespace MusicPlayer::API {

    struct APIDJCategoryExcludeHotData {
        QVector<APIDJCategoryItemData> data;
        static APIDJCategoryExcludeHotData
        fromJsonValue(const QJsonValue& json);
    };
}

