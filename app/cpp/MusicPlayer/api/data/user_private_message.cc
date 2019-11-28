//
// Created by HUANG WEN JUN on 2019/11/26.
//

#include "user_private_message.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    APIUserPrivateMessageUserData APIUserPrivateMessageUserData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("userId"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("nickname"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("avatarImgId"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("userType"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("vipType"))),
            Util::fromJsonValue<long>(object.value(QLatin1Literal("birthday"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("avatarUrl"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("backgroundUrl"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("gender"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("accountStatus"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("city"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("authStatus"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("detailDescription"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("defaultAvatar"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("djStatus"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("followed"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("description"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("signature"))),
        };
    }

    bool APIUserPrivateMessageUserData::operator==(const APIUserPrivateMessageUserData& other) const {
        return userId == other.userId && nickname == other.nickname && avatarImgId == other.avatarImgId &&
               userType == other.userType && vipType == other.vipType && birthday == other.birthday &&
               avatarUrl == other.avatarUrl && backgroundUrl == other.backgroundUrl && gender == other.gender &&
               accountStatus == other.accountStatus && city == other.city && authStatus == other.authStatus &&
               detailDescription == other.detailDescription && defaultAvatar == other.defaultAvatar &&
               djStatus == other.djStatus && followed == other.followed && description == other.description &&
               signature == other.signature;
    }

    bool APIUserPrivateMessageUserData::operator!=(const APIUserPrivateMessageUserData& other) const { return !operator==(other); }

    APIUserPrivateMessageData APIUserPrivateMessageData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("noticeAccountFlag"))),
            Util::fromJsonValue<long>(object.value(QLatin1Literal("lastMsgTime"))),
            Util::fromJsonValue<QString>(object.value(QLatin1Literal("lastMsg"))),
            Util::fromJsonValue<APIUserPrivateMessageUserData>(object.value(QLatin1Literal("fromUser"))),
            Util::fromJsonValue<APIUserPrivateMessageUserData>(object.value(QLatin1Literal("toUser"))),
        };
    }

    bool APIUserPrivateMessageData::operator==(const APIUserPrivateMessageData& other) const {
        return noticeAccountFlag == other.noticeAccountFlag && lastMsgTime == other.lastMsgTime && lastMsg == other.lastMsg &&
               fromUser == other.fromUser && toUser == other.toUser;
    }
    bool APIUserPrivateMessageData::operator!=(const APIUserPrivateMessageData& other) const { return !operator==(other); }

    APIUserPrivateMessagesData APIUserPrivateMessagesData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("more"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("newMsgCount"))),
            Util::jsonArrayToVariantList<APIUserPrivateMessageData>(object.value(QLatin1Literal("msgs"))),
        };
    }
    bool APIUserPrivateMessagesData::operator==(const APIUserPrivateMessagesData& other) const {
        return more == other.more && newMsgCount == other.newMsgCount && msgs == other.msgs;
    }
    bool APIUserPrivateMessagesData::operator!=(const APIUserPrivateMessagesData& other) const { return !operator==(other); }
} // namespace MusicPlayer::API
