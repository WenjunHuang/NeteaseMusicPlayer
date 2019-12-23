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
            Util::fromJsonValue<int>(object.value(QLatin1String("id"))),
            Util::fromJsonValue<QString>(
                object.value(QLatin1String("userName"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("type"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("status"))),
            Util::fromJsonValue<long>(
                object.value(QLatin1String("createTime"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("salt"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("vipType"))),
            Util::fromJsonValue<int>(
                object.value(QLatin1String("viptypeVersion"))),
        };
    }

    APIUserProfileData
    APIUserProfileData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1String("userId"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("vipType"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("gender"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("avatarImgId"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("birthday"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("city"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("accountStatus"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("nickname"))),
            Util::fromJsonValue<bool>(object.value(QLatin1String("followed"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("description"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("detailDescription"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("djStatus"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("userType"))),
            Util::fromJsonValue<bool>(object.value(QLatin1String("defaultAvatar"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("avatarUrl"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("backgroundUrl"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("followeds"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("follows"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("playlistCount"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("playlistBeSubscribedCount"))),
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
            Util::fromJsonValue<int>(object.value(QLatin1String("loginType"))),
            Util::fromJsonValue<APIUserAccountData>(object.value(QLatin1String("account"))),
            Util::fromJsonValue<APIUserProfileData>(object.value(QLatin1String("profile"))),
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
