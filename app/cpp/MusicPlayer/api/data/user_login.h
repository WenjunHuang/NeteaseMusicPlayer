//
// Created by rick on 2019/11/11.
//

#pragma once
#include <QString>
#include "../../util/json.h"

namespace MusicPlayer::API {
    using namespace MusicPlayer::Util;
    struct APIUserAccountData {
        int id;
        QString userName;
        int type;
        int status;
        long createTime;
        QString salt;
        int vipType;
        int viptypeVersion;

        static  APIUserAccountData fromJsonValue(const QJsonValue& json) {
          auto object = json.toObject();
          return {
            Util::fromJsonValue<int>(object.value(QLatin1Literal("id"))),
              Util::fromJsonValue<QString>(object.value(QLatin1Literal("userName"))),
                Util::fromJsonValue<int>(object.value(QLatin1Literal("type"))),
            Util::fromJsonValue<int>(object.value(QLatin1Literal("status"))),
            Util::fromJsonValue<long>(object.value(QLatin1Literal("createTime"))),
          }
        }
    };
    struct APIUserLoginData {
       int loginType;
       QString cookieToken;
    };
}
