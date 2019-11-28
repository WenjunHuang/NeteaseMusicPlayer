//
// Created by HUANG WEN JUN on 2019/11/26.
//
#include "user_login.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    APIUserAccountData APIUserAccountData::fromJsonValue(
        const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<QString>(
                object.value(QLatin1Literal("userName"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("type"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("status"))),
            Util::fromJsonValue<long>(
                object.value(QLatin1Literal("createTime"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("salt"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("vipType"))),
            Util::fromJsonValue<int>(
                object.value(QLatin1Literal("viptypeVersion"))),
        };
    }

    APIUserProfileData
    APIUserProfileData::fromJsonValue(const QJsonValue& json) {
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

    bool APIUserProfileData::operator==(const APIUserProfileData& other) const{
        return userId==other.userId &&
               vipType == other.vipType &&
               gender == other.gender &&
               avatarImgId == other.avatarImgId &&
               birthday == other.birthday &&
               city == other.city &&
               accountStatus == other.accountStatus &&
               nickname == other.nickname &&
               followed == other.followed &&
               description == other.description &&
               detailDescription == other.detailDescription &&
               djStatus == other.djStatus &&
               userType == other.userType &&
               defaultAvatar == other.defaultAvatar &&
               avatarUrl == other.avatarUrl &&
               backgroundUrl == other.backgroundUrl &&
               followeds == other.followeds &&
               follows == other.follows &&
               eventCount == other.eventCount &&
               playlistCount == other.playlistCount &&
               playlistBeSubscribedCount == other.playlistBeSubscribedCount;
    }
    bool APIUserProfileData::operator!=(const APIUserProfileData& other) const {
        return !operator==(other);
    }

    APIUserLoginData APIUserLoginData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("loginType"))),
            Util::fromJsonValue<APIUserAccountData>(object.value(QLatin1Literal("account"))),
            Util::fromJsonValue<APIUserProfileData>(object.value(QLatin1Literal("profile"))),
            std::nullopt,
        };
    }

    bool APIUserLoginData::operator==(const APIUserLoginData& other) const {
        return loginType == other.loginType && account == other.account &&
               profile == other.profile;
    }

    bool APIUserLoginData::operator!=(const APIUserLoginData& other) const {
        return !operator==(other);
    }

    bool APIUserAccountData::operator==(
        const MusicPlayer::API::APIUserAccountData& other) const {
        return id == other.id &&
               userName == other.userName &&
               type == other.type &&
               status == other.status &&
               createTime == other.createTime &&
               salt == other.salt &&
               vipType == other.vipType &&
               viptypeVersion == other.viptypeVersion;
    }
    bool APIUserAccountData::operator!=(const APIUserAccountData& other) const {
        return !operator==(other);
    }
}
