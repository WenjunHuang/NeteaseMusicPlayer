//
// Created by HUANG WEN JUN on 2019/11/26.
//

#include "user_private_message.h"
#include "../../util/json.h"

namespace MusicPlayer::API {
    APIUserPrivateMessageUserData APIUserPrivateMessageUserData::fromJsonValue(const QJsonValue& json) {
        auto object = json.toObject();
        return {
            Util::fromJsonValue<int>(object.value(QLatin1String("userId"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("nickname"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("avatarImgId"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("userType"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("vipType"))),
            Util::fromJsonValue<long>(object.value(QLatin1String("birthday"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("avatarUrl"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("backgroundUrl"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("gender"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("accountStatus"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("city"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("authStatus"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("detailDescription"))),
            Util::fromJsonValue<bool>(object.value(QLatin1String("defaultAvatar"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("djStatus"))),
            Util::fromJsonValue<bool>(object.value(QLatin1String("followed"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("description"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("signature"))),
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
            Util::fromJsonValue<bool>(object.value(QLatin1String("noticeAccountFlag"))),
            Util::fromJsonValue<long>(object.value(QLatin1String("lastMsgTime"))),
            Util::fromJsonValue<QString>(object.value(QLatin1String("lastMsg"))),
            Util::fromJsonValue<APIUserPrivateMessageUserData>(object.value(QLatin1String("fromUser"))),
            Util::fromJsonValue<APIUserPrivateMessageUserData>(object.value(QLatin1String("toUser"))),
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
            Util::fromJsonValue<bool>(object.value(QLatin1String("more"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("newMsgCount"))),
            Util::fromJsonArray<APIUserPrivateMessageData>(object.value(QLatin1String("msgs"))),
        };
    }
    bool APIUserPrivateMessagesData::operator==(const APIUserPrivateMessagesData& other) const {
        return more == other.more && newMsgCount == other.newMsgCount && msgs == other.msgs;
    }
    bool APIUserPrivateMessagesData::operator!=(const APIUserPrivateMessagesData& other) const { return !operator==(other); }
} // namespace MusicPlayer::API
