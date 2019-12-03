#pragma once
#include <QtCore>

namespace MusicPlayer::API {
    struct APISongPrivilegeData {
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

        bool operator==(const APISongPrivilegeData& other) const;
        bool operator!=(const APISongPrivilegeData& other) const;

        static APISongPrivilegeData fromJsonValue(const QJsonValue& json);
    };
}
