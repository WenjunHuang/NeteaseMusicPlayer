//
// Created by HUANG WEN JUN on 2019/11/12.
//
#pragma once
#include "../../util/json.h"
#include <QtCore>

namespace MusicPlayer::API {
    struct APIUserPrivateMessageUserData {
        int userId;
        QString nickname;
        int avatarImgId;
        int userType;
        int vipType;
        long birthday;
        QString avatarUrl;
        QString backgroundUrl;
        int gender;
        int accountStatus;
        int city;
        int authStatus;
        QString detailDescription;
        bool defaultAvatar;
        int djStatus;
        bool followed;
        QString description;
        QString signature;

        static APIUserPrivateMessageUserData
        fromJsonValue(const QJsonValue& json) {
            auto object = json.toObject();
            return {
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("userId"))),
                Util::fromJsonValue<QString>(
                    object.value(QLatin1Literal("nickname"))),
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("avatarImgId"))),
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("userType"))),
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("vipType"))),
                Util::fromJsonValue<long>(
                    object.value(QLatin1Literal("birthday"))),
                Util::fromJsonValue<QString>(
                    object.value(QLatin1Literal("avatarUrl"))),
                Util::fromJsonValue<QString>(
                    object.value(QLatin1Literal("backgroundUrl"))),
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("gender"))),
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("accountStatus"))),
                Util::fromJsonValue<int>(object.value(QLatin1Literal("city"))),
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("authStatus"))),
                Util::fromJsonValue<QString>(
                    object.value(QLatin1Literal("detailDescription"))),
                Util::fromJsonValue<bool>(
                    object.value(QLatin1Literal("defaultAvatar"))),
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("djStatus"))),
                Util::fromJsonValue<bool>(
                    object.value(QLatin1Literal("followed"))),
                Util::fromJsonValue<QString>(
                    object.value(QLatin1Literal("description"))),
                Util::fromJsonValue<QString>(
                    object.value(QLatin1Literal("signature"))),
            };
        }
    };
    struct APIUserPrivateMessageData {
        bool noticeAccountFlag;
        long lastMsgTime;
        QString lastMsg;
        APIUserPrivateMessageUserData fromUser;
        APIUserPrivateMessageUserData toUser;

        static APIUserPrivateMessageData fromJsonValue(const QJsonValue& json) {
            auto object = json.toObject();
            return {
                Util::fromJsonValue<bool>(
                    object.value(QLatin1Literal("noticeAccountFlag"))),
                Util::fromJsonValue<long>(
                    object.value(QLatin1Literal("lastMsgTime"))),
                Util::fromJsonValue<QString>(
                    object.value(QLatin1Literal("lastMsg"))),
                Util::fromJsonValue<APIUserPrivateMessageUserData>(
                    object.value(QLatin1Literal("fromUser"))),
                Util::fromJsonValue<APIUserPrivateMessageUserData>(
                    object.value(QLatin1Literal("toUser"))),
            };
        }
    };
    struct APIUserPrivateMessagesData {
        bool more;
        int newMsgCount;
        QVector<APIUserPrivateMessageData> msgs;

        static APIUserPrivateMessagesData
        fromJsonValue(const QJsonValue& json) {
            auto object = json.toObject();
            return {
                Util::fromJsonValue<bool>(object.value(QLatin1Literal("more"))),
                Util::fromJsonValue<int>(
                    object.value(QLatin1Literal("newMsgCount"))),
                Util::fromJsonArray<APIUserPrivateMessageData>(
                    object.value(QLatin1Literal("msgs"))),
            };
        }
    };
} // namespace MusicPlayer::API
