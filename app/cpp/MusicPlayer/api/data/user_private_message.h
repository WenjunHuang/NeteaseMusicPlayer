//
// Created by HUANG WEN JUN on 2019/11/12.
//
#pragma once
#include <QtCore>

namespace MusicPlayer::API {
    struct APIUserPrivateMessageUserData {
        Q_GADGET
        Q_PROPERTY(int userId MEMBER userId)
        Q_PROPERTY(QString nickname MEMBER nickname)
        Q_PROPERTY(int avatarImgId MEMBER avatarImgId)
        Q_PROPERTY(int userType MEMBER userType)
        Q_PROPERTY(int vipType MEMBER vipType)
        Q_PROPERTY(long birthday MEMBER birthday)
        Q_PROPERTY(QUrl avatarUrl MEMBER avatarUrl)
        Q_PROPERTY(QString backgroundUrl MEMBER backgroundUrl)
        Q_PROPERTY(int gender MEMBER gender)
        Q_PROPERTY(int accountStatus MEMBER accountStatus)
        Q_PROPERTY(int city MEMBER city)
        Q_PROPERTY(int authStatus MEMBER authStatus)
        Q_PROPERTY(QString detailDescription MEMBER detailDescription)
        Q_PROPERTY(bool defaultAvatar MEMBER defaultAvatar)
        Q_PROPERTY(int djStatus MEMBER djStatus)
        Q_PROPERTY(bool followed MEMBER followed)
        Q_PROPERTY(QString description MEMBER description)
        Q_PROPERTY(QString signature MEMBER signature)

      public:
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
        Q_GADGET
        Q_PROPERTY(bool noticeAccountFlag MEMBER noticeAccountFlag)
        Q_PROPERTY(long lastMsgTime MEMBER lastMsgTime)
        Q_PROPERTY(QString lastMsg MEMBER lastMsg)
        Q_PROPERTY(APIUserPrivateMessageUserData fromUser MEMBER fromUser)
        Q_PROPERTY(APIUserPrivateMessageUserData toUser MEMBER toUser)
      public:
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
        Q_GADGET
        Q_PROPERTY(bool more MEMBER more)
        Q_PROPERTY(int newMsgCount MEMBER newMsgCount)
        Q_PROPERTY(QVariantList msgs MEMBER msgs)
      public:
        bool more;
        int newMsgCount;
        QVariantList msgs;

        bool operator==(const APIUserPrivateMessagesData& other) const;

        bool operator!=(const APIUserPrivateMessagesData& other) const;

        static APIUserPrivateMessagesData fromJsonValue(const QJsonValue& json);
    };
} // namespace MusicPlayer::API

Q_DECLARE_METATYPE(MusicPlayer::API::APIUserPrivateMessageData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIUserPrivateMessagesData)
Q_DECLARE_METATYPE(MusicPlayer::API::APIUserPrivateMessageUserData)
