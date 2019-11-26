//
// Created by HUANG WEN JUN on 2019/11/26.
//
#include "song_privilege.h"
#include "../../util/json.h"
namespace MusicPlayer::API {
    APISongPrivilegeData
    APISongPrivilegeData::fromJsonValue(const QJsonValue& json) {
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
    bool APISongPrivilegeData::operator==(const APISongPrivilegeData& other) {
        return memcmp(this,&other,sizeof(APISongPrivilegeData));
    }
    bool APISongPrivilegeData::operator!=(const APISongPrivilegeData& other) {
        return !operator==(other);
    }
}
