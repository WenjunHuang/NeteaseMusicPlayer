
#pragma once

#include <QtCore>

namespace MusicPlayer::API {

    struct APIDJCategoryRecommendItemRadioData {
        Q_GADGET
        Q_PROPERTY(int id MEMBER id)
        Q_PROPERTY(QString name MEMBER name)
        Q_PROPERTY(QString rcmdText MEMBER rcmdText)
        Q_PROPERTY(int radioFeeType MEMBER radioFeeType)
        Q_PROPERTY(int feeScope MEMBER feeScope)
        Q_PROPERTY(QUrl picUrl MEMBER picUrl)
        Q_PROPERTY(int programCount MEMBER programCount)
        Q_PROPERTY(QString alg MEMBER alg)
        Q_PROPERTY(QVariant playCount MEMBER playCount)
        Q_PROPERTY(QString lastProgramName MEMBER lastProgramName)
      public:
        int id;
        QString name;
        QString rcmdText;
        int radioFeeType;
        int feeScope;
        QUrl picUrl;
        int programCount;
        //        optional<int> playCount;
        QVariant playCount; // optional<int>
        QString alg;
        QString lastProgramName;

        bool operator==(const APIDJCategoryRecommendItemRadioData& other);
        bool operator!=(const APIDJCategoryRecommendItemRadioData& other);

        static APIDJCategoryRecommendItemRadioData
        fromJsonValue(const QJsonValue& json);
    };

    struct APIDJCategoryRecommendItemData {
        Q_GADGET
        Q_PROPERTY(int categoryId MEMBER categoryId)
        Q_PROPERTY(QString categoryName MEMBER categoryName)
        Q_PROPERTY(QVariantList radios MEMBER radios)
      public:
        int categoryId;
        QString categoryName;
        //        QVector<APIDJCategoryRecommendItemRadioData> radios;
        QVariantList radios;

        bool operator==(const APIDJCategoryRecommendItemData& other);

        bool operator!=(const APIDJCategoryRecommendItemData& other);

        static APIDJCategoryRecommendItemData
        fromJsonValue(const QJsonValue& json);
    };

    struct APIDJCategoryRecommendData {
        Q_GADGET
        Q_PROPERTY(QVariantList data MEMBER data)
      public:
        QVariantList data;

        bool operator==(const APIDJCategoryRecommendData& other);

        bool operator!=(const APIDJCategoryRecommendData& other);

        static APIDJCategoryRecommendData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API

Q_DECLARE_METATYPE(MusicPlayer::API::APIDJCategoryRecommendData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIDJCategoryRecommendItemData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIDJCategoryRecommendItemRadioData)
