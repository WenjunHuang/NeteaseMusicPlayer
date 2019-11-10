#pragma once
#include <QJsonValue>
#include <QJsonObject>
#include "../../util/json.h"

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;
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

        static APISongPrivilegeData fromJsonValue(const QJsonValue& json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("fee"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("payed"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("st"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("pl"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("dl"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("sp"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("cp"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("subp"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("cs"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("maxbr"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("fl"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("toast"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("flag"))),
            Util::fromJsonValue<bool>(object.value(QLatin1Literal("preSell"))),
          };
        }
    };
}