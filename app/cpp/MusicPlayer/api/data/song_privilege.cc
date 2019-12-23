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
            Util::fromJsonValue<int>(object.value(QLatin1String("id"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("fee"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("payed"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("st"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("pl"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("dl"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("sp"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("cp"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("subp"))),
            Util::fromJsonValue<bool>(object.value(QLatin1String("cs"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("maxbr"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("fl"))),
            Util::fromJsonValue<bool>(object.value(QLatin1String("toast"))),
            Util::fromJsonValue<int>(object.value(QLatin1String("flag"))),
            Util::fromJsonValue<bool>(object.value(QLatin1String("preSell"))),
        };
    }
    bool APISongPrivilegeData::operator==(const APISongPrivilegeData& other) const {
        return memcmp(this,&other,sizeof(APISongPrivilegeData));
    }
    bool APISongPrivilegeData::operator!=(const APISongPrivilegeData& other) const {
        return !operator==(other);
    }
}
