
#pragma once

#include <optional>
#include <QtCore>

namespace MusicPlayer::API {

    struct APIDJCategoryRecommendItemRadioData {
        int id;
        QString name;
        QString rcmdText;
        int radioFeeType;
        int feeScope;
        QUrl picUrl;
        int programCount;
        std::optional<int> playCount;
        QString alg;
        QString lastProgramName;

        bool operator==(const APIDJCategoryRecommendItemRadioData& other) const;
        bool operator!=(const APIDJCategoryRecommendItemRadioData& other) const;

        static APIDJCategoryRecommendItemRadioData fromJsonValue(const QJsonValue& json);
    };

    struct APIDJCategoryRecommendItemData {
        int categoryId;
        QString categoryName;
        QVector<APIDJCategoryRecommendItemRadioData> radios;

        bool operator==(const APIDJCategoryRecommendItemData& other) const;

        bool operator!=(const APIDJCategoryRecommendItemData& other) const;

        static APIDJCategoryRecommendItemData fromJsonValue(const QJsonValue& json);
    };

    struct APIDJCategoryRecommendData {
        QVector<APIDJCategoryRecommendItemData> data;

        bool operator==(const APIDJCategoryRecommendData& other) const;

        bool operator!=(const APIDJCategoryRecommendData& other) const;

        static APIDJCategoryRecommendData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API

