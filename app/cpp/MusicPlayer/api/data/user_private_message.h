//
// Created by HUANG WEN JUN on 2019/11/12.
//
#pragma once
#include <QtCore>

namespace MusicPlayer::API {
    struct APIUserPrivateMessageUserData {
        int userId;
        QString nickname;
        int avatarImgId;
        int userType;
        int vipType;
        long birthday;
        QUrl avatarUrl;
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

        bool operator==(const APIUserPrivateMessageUserData& other)const;

        bool operator!=(const APIUserPrivateMessageUserData& other)const;

        static APIUserPrivateMessageUserData
        fromJsonValue(const QJsonValue& json);
    };

    struct APIUserPrivateMessageData {
        bool noticeAccountFlag;
        long lastMsgTime;
        QString lastMsg;
        APIUserPrivateMessageUserData fromUser;
        APIUserPrivateMessageUserData toUser;

        bool operator==(const APIUserPrivateMessageData& other)const;

        bool operator!=(const APIUserPrivateMessageData& other)const;

        static APIUserPrivateMessageData fromJsonValue(const QJsonValue& json);
    };

    struct APIUserPrivateMessagesData {
        bool more;
        int newMsgCount;
        QVector<APIUserPrivateMessageData> msgs;

        bool operator==(const APIUserPrivateMessagesData& other) const;

        bool operator!=(const APIUserPrivateMessagesData& other) const;

        static APIUserPrivateMessagesData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API
