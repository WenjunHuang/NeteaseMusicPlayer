//
// Created by rick on 2019/11/7.
//

#pragma once

#include "data/error.h"
#include "http.h"
#include "data/dj_banner.h"
#include "data/dj_category_excludehot.h"
#include "data/dj_category_recommend.h"
#include "data/personalized_newsong.h"
#include "data/banner.h"
#include "data/personalized.h"
#include "data/user_private_message.h"
#include <QFuture>
#include <QJsonDocument>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <exception>
#include <variant>
#include "data/user_login.h"

namespace MusicPlayer::API {
    template<typename T> using Response = std::variant<Error, T>;
    template<typename T> using APIResponse = QFuture<Response<T>>;

    class MusicAPI {
    public:
        APIResponse<APIDJBannersData> djBanner();

        APIResponse<APIDJCategoryExcludeHotData> djCategoryExcludeHot();

        APIResponse<APIDJCategoryRecommendData> djCategoryRecommend();

        // 首页轮播图
        APIResponse<APIBannersData> banner();

        // 推荐新歌
        APIResponse<APIPersonalizedNewSongData> personalizedNewSong();

        // 推荐歌单
        APIResponse<APIPersonalizedData> personalized(int limit = 30);

        // 用户手机登录
        APIResponse<APIUserLoginData> loginCellphone(const QString& cellphone,const QString& password);

        // 用户私信
        APIResponse<APIUserPrivateMessagesData> userPrivateMessages(const QString& cookieToken,int limit = 30,int offset = 0);
    };
} // namespace MusicPlayer::MusicAPI

