//
// Created by rick on 2019/11/11.
//

#pragma once

#include <QtCore>
#include <optional>

namespace MusicPlayer::API {
    struct APIUserAccountData {
        Q_GADGET
        Q_PROPERTY(int id MEMBER id)
        Q_PROPERTY(QString userName MEMBER userName)
        Q_PROPERTY(int type MEMBER type)
        Q_PROPERTY(int status MEMBER status)
        Q_PROPERTY(long createTime MEMBER createTime)
        Q_PROPERTY(QString salt MEMBER salt)
        Q_PROPERTY(int vipType MEMBER vipType)
        Q_PROPERTY(int viptypeVersion MEMBER viptypeVersion)

      public:
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
        Q_GADGET
        Q_PROPERTY(int userId MEMBER userId)
        Q_PROPERTY(int vipType MEMBER vipType)
        Q_PROPERTY(int gender MEMBER gender)
        Q_PROPERTY(int avatarImgId MEMBER avatarImgId)
        Q_PROPERTY(int birthday MEMBER birthday)
        Q_PROPERTY(int city MEMBER city)
        Q_PROPERTY(int accountStatus MEMBER accountStatus)
        Q_PROPERTY(QString nickname MEMBER nickname)
        Q_PROPERTY(bool followed MEMBER followed)
        Q_PROPERTY(QString description MEMBER description)
        Q_PROPERTY(QString detailDescription MEMBER detailDescription)
        Q_PROPERTY(int djStatus MEMBER djStatus)
        Q_PROPERTY(int userType MEMBER userType)
        Q_PROPERTY(bool defaultAvatar MEMBER defaultAvatar)
        Q_PROPERTY(QString avatarUrl MEMBER avatarUrl)
        Q_PROPERTY(QString backgroundUrl MEMBER backgroundUrl)
        Q_PROPERTY(int followeds MEMBER followeds)
        Q_PROPERTY(int follows MEMBER follows)
        Q_PROPERTY(int eventCount MEMBER eventCount)
        Q_PROPERTY(int playlistCount MEMBER playlistCount)
        Q_PROPERTY(
            int playlistBeSubscribedCount MEMBER playlistBeSubscribedCount)

      public:
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

Q_DECLARE_METATYPE(MusicPlayer::API::APIUserAccountData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIUserProfileData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIUserLoginData)
