//
// Created by rick on 2019/11/7.
//

#pragma once

#include "data/banner.h"
#include "data/dj_banner.h"
#include "data/dj_category_excludehot.h"
#include "data/dj_category_recommend.h"
#include "data/error.h"
#include "data/personalized.h"
#include "data/personalized_newsong.h"
#include "data/playlist_catlist.h"
#include "data/user_login.h"
#include "data/user_private_message.h"
#include "http.h"
#include <QFuture>
#include <QFutureWatcher>
#include <QJsonDocument>
#include <QtConcurrent/QtConcurrent>
#include <exception>
#include <folly/futures/Future.h>
#include <variant>

namespace MusicPlayer::API {
    template <typename T> using Response    = std::variant<APIError, T>;
    template <typename T> using APIResponse = folly::SemiFuture<Response<T>>;

    class MusicAPI {
      public:
        APIResponse<APIDJBannersData> djBanner();

        APIResponse<APIDJCategoryExcludeHotData> djCategoryExcludeHot();

        APIResponse<APIDJCategoryRecommendData> djCategoryRecommend();

        APIResponse<APIBannersData> banner();

        APIResponse<APIPersonalizedNewSongData> personalizedNewSong();

        APIResponse<APIPersonalizedData> personalized(int limit = 30);

        APIResponse<APIUserLoginData> loginCellphone(const QString& cellphone, const QString& password);

        APIResponse<APIUserPrivateMessagesData> userPrivateMessages(const QString& cookieToken, int limit = 30, int offset = 0);

        APIResponse<APIPlaylistCatListData> playlistCatlist();

      public:
        // 向meta type system注册，程序启动时必须调用
        static void registerTypes();
    };
} // namespace MusicPlayer::API
