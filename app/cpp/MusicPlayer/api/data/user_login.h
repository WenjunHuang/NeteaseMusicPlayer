//
// Created by rick on 2019/11/11.
//

#pragma once

#include <QtCore>
#include <optional>

namespace MusicPlayer::API {
    struct APIUserAccountData {
        int id;
        QString userName;
        int type;
        int status;
        long createTime;
        QString salt;
        int vipType;
        int viptypeVersion;

        bool operator==(const APIUserAccountData& other) const;

        bool operator!=(const APIUserAccountData& other) const;

        static APIUserAccountData fromJsonValue(const QJsonValue& json);
    };

    struct APIUserProfileData {
        int userId;
        int vipType;
        int gender;
        int avatarImgId;
        int birthday;
        int city;
        int accountStatus;
        QString nickname;
        bool followed;
        QString description;
        QString detailDescription;
        int djStatus;
        int userType;
        bool defaultAvatar;
        QString avatarUrl;
        QString backgroundUrl;
        int followeds;
        int follows;
        int eventCount;
        int playlistCount;
        int playlistBeSubscribedCount;

        bool operator==(const APIUserProfileData& other) const;

        bool operator!=(const APIUserProfileData& other) const;

        static APIUserProfileData fromJsonValue(const QJsonValue& json);
    };

    struct APIUserLoginData {
        Q_GADGET
        Q_PROPERTY(int loginType MEMBER loginType)
        Q_PROPERTY(APIUserAccountData account MEMBER account)
        Q_PROPERTY(APIUserProfileData profile MEMBER profile)

      public:
        int loginType;
        APIUserAccountData account;
        APIUserProfileData profile;
        std::optional<QString> cookieToken = std::nullopt;

        bool operator==(const APIUserLoginData& other) const;

        bool operator!=(const APIUserLoginData& other) const;

        static APIUserLoginData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API
