//
// Created by rick on 2019/11/25.
//
#include "dj_category_excludehot.h"
#include "../../util/json.h"

namespace MusicPlayer::API {

    APIDJCategoryItemData
    API::APIDJCategoryItemData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("name")))};
    }

    bool APIDJCategoryItemData::operator==(const APIDJCategoryItemData& other) {
        return id == other.id && name == other.name;
    }

    bool APIDJCategoryItemData::operator!=(const APIDJCategoryItemData& other) {
        return !operator==(other);
    }

    APIDJCategoryExcludeHotData
    APIDJCategoryExcludeHotData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {Util::jsonArrayToVariantList<APIDJCategoryItemData>(
            object.value(QLatin1Literal("data")))};
    }

    bool APIDJCategoryExcludeHotData::operator==(
        const APIDJCategoryExcludeHotData& other) {
        return data==other.data;
    }

    bool APIDJCategoryExcludeHotData::operator!=(
        const APIDJCategoryExcludeHotData& other) {
        return !operator==(other);
    }
} // namespace MusicPlayer::API
