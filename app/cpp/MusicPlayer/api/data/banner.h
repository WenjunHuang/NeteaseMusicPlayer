#pragma once

#include <QtCore>

namespace MusicPlayer::API {
    struct APIBannerData {
        QUrl imageUrl;
        int targetId;
        int targetType;
        QString titleColor;
        QString typeTitle;
        bool exclusive;
        QString encodeId;
        QString scm;

        bool operator==(const APIBannerData& other) const;

        bool operator!=(const APIBannerData& other) const;

        static APIBannerData fromJsonValue(const QJsonValue& json);
    };

    struct APIBannersData {
        QVector<APIBannerData> banners;

        bool operator==(const APIBannersData& other) const;

        bool operator!=(const APIBannersData& other) const;

        static APIBannersData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API
