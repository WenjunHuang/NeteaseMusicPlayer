//
// Created by rick on 2019/11/25.
//
#include "dj_category_recommend.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    APIDJCategoryRecommendItemRadioData APIDJCategoryRecommendItemRadioData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
                Util::fromJsonValue<QString>(object.value(QLatin1Literal("name"))),
                Util::fromJsonValue<QString>(object.value(QLatin1Literal("rcmdText"))),
                Util::fromJsonValue<int>(object.value(QLatin1Literal("radioFeeType"))),
                Util::fromJsonValue<int>(object.value(QLatin1Literal("feeScope"))),
                Util::fromJsonValue<QString>(object.value(QLatin1Literal("picUrl"))),
                Util::fromJsonValue<int>(object.value(QLatin1Literal("programCount"))),
                Util::jsonValueToVariant<int>(object.value(QLatin1Literal("playCount"))),
                Util::fromJsonValue<QString>(object.value(QLatin1Literal("alg"))),
                Util::fromJsonValue<QString>(object.value(QLatin1Literal("lastProgramName")))};
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
            Util::fromJsonValue<int>(object.value(QLatin1Literal("categoryId"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("categoryName"))),
            Util::jsonArrayToVariantList<APIDJCategoryRecommendItemRadioData>(object.value(QLatin1Literal("radios"))),
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
        return {Util::jsonArrayToVariantList<APIDJCategoryRecommendItemData>(object.value(QLatin1Literal("data")))};
    }

    bool APIDJCategoryRecommendData::operator==(const APIDJCategoryRecommendData& other) const { return data == other.data; }

    bool APIDJCategoryRecommendData::operator!=(const APIDJCategoryRecommendData& other) const { return !operator==(other); }
} // namespace MusicPlayer::API
