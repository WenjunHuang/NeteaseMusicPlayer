//
// Created by rick on 2019/11/7.
//

#pragma once

#include "../commons.h"
#include "data/data.h"
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

        // 精品歌单
        APIResponse<APITopPlayListData> topPlaylistHighQuality(const QString& cat = "全部", int limit = 50, qint64 before = 0);

        // 歌单详情
        APIResponse<APIPlayListDetailData> playlistDetail(int playlistId);

        // 分类歌单
        APIResponse<APITopPlayListData> topPlaylist(const QString& cat, int limit = 50, int offset = 0);

        // 电台分类
        APIResponse<APIDJCategoryListData> djCatList();

        // 歌曲详情
        APIResponse<QString> songDetail(const QVector<int>& songIds);

        // 歌曲url
        APIResponse<APISongUrlData> songUrl(SongId songId, SongQuality songQuality = SongQuality::Q990000);

        // 歌手介绍
        APIResponse<QString> artistDesc(ArtistId artistId);

      public:
        // 向meta type system注册，程序启动时必须调用
        static void registerTypes();
    };
} // namespace MusicPlayer::API