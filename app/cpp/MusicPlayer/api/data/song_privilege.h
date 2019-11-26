#pragma once
#include <QtCore>

namespace MusicPlayer::API {
    struct APISongPrivilegeData {
        Q_GADGET
        Q_PROPERTY(int id MEMBER id)
        Q_PROPERTY(int fee MEMBER fee)
        Q_PROPERTY(int payed MEMBER payed)
        Q_PROPERTY(int st MEMBER st)
        Q_PROPERTY(int pl MEMBER pl)
        Q_PROPERTY(int dl MEMBER dl)
        Q_PROPERTY(int sp MEMBER sp)
        Q_PROPERTY(int cp MEMBER cp)
        Q_PROPERTY(int subp MEMBER subp)
        Q_PROPERTY(bool cs MEMBER cs)
        Q_PROPERTY(int maxbr MEMBER maxbr)
        Q_PROPERTY(int fl MEMBER fl)
        Q_PROPERTY(bool toast MEMBER toast)
        Q_PROPERTY(int flag MEMBER flag)
        Q_PROPERTY(bool preSell MEMBER preSell)

      public:
        int id;
        int fee;
        int payed;
        int st;
        int pl;
        int dl;
        int sp;
        int cp;
        int subp;
        bool cs;
        int maxbr;
        int fl;
        bool toast;
        int flag;
        bool preSell;

        bool operator==(const APISongPrivilegeData& other);
        bool operator!=(const APISongPrivilegeData& other);

        static APISongPrivilegeData fromJsonValue(const QJsonValue& json);
    };
}
Q_DECLARE_METATYPE(MusicPlayer::API::APISongPrivilegeData)