//
// Created by rick on 2019/11/25.
//
#include "dj_category_excludehot.h"
#include "../../util/json.h"

namespace MusicPlayer::API {

    APIDJCategoryExcludeHotData
    APIDJCategoryExcludeHotData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {Util::fromJsonArray<APIDJCategoryItemData>(
            object.value(QLatin1String("data")))};
    }

} // namespace MusicPlayer::API
