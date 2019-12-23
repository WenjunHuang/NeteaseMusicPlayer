//
// Created by rick on 2019/11/25.
//
#include "dj_category_recommend.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    APIDJCategoryRecommendItemRadioData APIDJCategoryRecommendItemRadioData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {Util::fromJsonValue<int>(object.value(QLatin1String("id"))),
                Util::fromJsonValue<QString>(object.value(QLatin1String("name"))),
                Util::fromJsonValue<QString>(object.value(QLatin1String("rcmdText"))),
                Util::fromJsonValue<int>(object.value(QLatin1String("radioFeeType"))),
                Util::fromJsonValue<int>(object.value(QLatin1String("feeScope"))),
                Util::fromJsonValue<QString>(object.value(QLatin1String("picUrl"))),
                Util::fromJsonValue<int>(object.value(QLatin1String("programCount"))),
                Util::fromOptionalJsonValue<int>(object.value(QLatin1String("playCount"))),
                Util::fromJsonValue<QString>(object.value(QLatin1String("alg"))),
                Util::fromJsonValue<QString>(object.value(QLatin1String("lastProgramName")))};
    }

    bool APIDJCategoryRecommendItemRadioData::operator==(const APIDJCategoryRecommendItemRadioData& other) const {
        return id == other.id && name == other.name && rcmdText == other.rcmdText && radioFeeType == other.radioFeeType &&
               feeScope == other.feeScope && picUrl == other.picUrl && programCount == other.programCount && alg == other.alg &&
               playCount == other.playCount && lastProgramName == other.lastProgramName;
    }

    bool APIDJCategoryRecommendItemRadioData::operator!=(const APIDJCategoryRecommendItemRadioData& other) const {
        return !operator==(other);
    }

    APIDJCategoryRecommendItemData APIDJCategoryRecommendItemData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1String("categoryId"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("categoryName"))),
            Util::fromJsonArray<APIDJCategoryRecommendItemRadioData>(object.value(QLatin1String("radios"))),
        };
    }

    bool APIDJCategoryRecommendItemData::operator==(const APIDJCategoryRecommendItemData& other) const {
        return categoryId == other.categoryId && categoryName == other.categoryName && radios == other.radios;
    }

    bool APIDJCategoryRecommendItemData::operator!=(const APIDJCategoryRecommendItemData& other) const {
        return !operator==(other);
    }

    APIDJCategoryRecommendData APIDJCategoryRecommendData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {Util::fromJsonArray<APIDJCategoryRecommendItemData>(object.value(QLatin1String("data")))};
    }

    bool APIDJCategoryRecommendData::operator==(const APIDJCategoryRecommendData& other) const { return data == other.data; }

    bool APIDJCategoryRecommendData::operator!=(const APIDJCategoryRecommendData& other) const { return !operator==(other); }
} // namespace MusicPlayer::API
