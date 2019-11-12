//
// Created by rick on 2019/11/11.
//

#pragma once

#include <QString>
#include "../../util/json.h"
#include <optional>

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;

    struct APIUserAccountData {
        int id;
        QString userName;
        int type;
        int status;
        long createTime;
        QString salt;
        int vipType;
        int viptypeVersion;

        static APIUserAccountData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("userName"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("type"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("status"))),
            Util::fromJsonValue<long>(object.value(QLatin1Literal("createTime"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("salt"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("vipType"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("viptypeVersion"))),
          };
        }
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

        static APIUserProfileData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("userId"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("vipType"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("gender"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("avatarImgId"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("birthday"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("city"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("accountStatus"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("nickname"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("followed"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("description"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("detailDescription"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("djStatus"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("userType"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("defaultAvatar"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("avatarUrl"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("backgroundUrl"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("followeds"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("follows"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("playlistCount"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("playlistBeSubscribedCount"))),
          };
        }
    };

    struct APIUserLoginData {
        int loginType;
        APIUserAccountData account;
        APIUserProfileData profile;

        std::optional<QString> cookieToken = std::nullopt;

        static APIUserLoginData fromJsonValue(const QJsonValue &json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("loginType"))),
            Util::fromJsonValue<APIUserAccountData>(object.value(QLatin1Literal("account"))),
            Util::fromJsonValue<APIUserProfileData>(object.value(QLatin1Literal("profile"))),
            std::nullopt,
          };
        }

    };
}
