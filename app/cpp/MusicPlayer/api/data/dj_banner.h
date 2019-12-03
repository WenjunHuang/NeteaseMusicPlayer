#pragma once

#include <QtCore>

namespace MusicPlayer::API {

    struct APIDJBannerData {
        int targetId;
        int targetType;
        QString pic;
        QUrl url;
        QString typeTitle;
        bool exclusive;

        bool operator==(const APIDJBannerData& other) const;
        bool operator!=(const APIDJBannerData& other) const;

        static APIDJBannerData fromJsonValue(const QJsonValue& value);
    };

    struct APIDJBannersData {
        QVector<APIDJBannerData> data;

        bool operator==(const APIDJBannersData& other) const;

        bool operator!=(const APIDJBannersData& other) const;

        static APIDJBannersData fromJsonValue(const QJsonValue& value);
    };
} // namespace MusicPlayer::API
