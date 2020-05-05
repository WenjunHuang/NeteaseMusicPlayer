//
// Created by HUANG WEN JUN on 2019/12/8.
//
#include "dj_catlist.h"
#include "../api_response.h"
#include "wobjectimpl.h"

namespace MusicPlayer::API {
    APIDJCategoryItemData APIDJCategoryItemData::fromJsonValue(const QJsonValue& jsonValue) {
        auto jsonObj = jsonValue.toObject();
        return {Util::fromJsonValue<int>(jsonObj.value(QLatin1String("id"))),
                Util::fromJsonValue<QString>(jsonObj.value(QLatin1String("pic_pc_white_url"))),
                Util::fromJsonValue<QString>(jsonObj.value(QLatin1String("name")))};
    }

    APIDJCategoryListData APIDJCategoryListData::fromJsonValue(const QJsonValue& jsonValue) {
        auto jsonObj = jsonValue.toObject();
        return {Util::fromJsonArray<APIDJCategoryItemData>(jsonObj.value(QLatin1String("categories")))};
    }
} // namespace Music
