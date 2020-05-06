//
// Created by rick on 2019/11/7.
//

#pragma once

#include "../commons.h"
#include "api_response.h"
#include "data/data.h"
#include "http.h"
#include <QJsonDocument>
#include <QtCore/QtCore>
#include <exception>
#include <variant>

namespace MusicPlayer::API {

    class MusicAPI : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(MusicAPI)
        MusicAPI();

      public:
        APIResponseHandler<APIDJBannersData>* djBanner();

        APIResponseHandler<APIDJCategoryExcludeHotData>* djCategoryExcludeHot();

        APIResponseHandler<APIDJCategoryRecommendData>* djCategoryRecommend();

        APIResponseHandler<APIBannersData>* banner();

        APIResponseHandler<APIPersonalizedNewSongData>* personalizedNewSong();

        APIResponseHandler<APIPersonalizedData>* personalized(int limit = 30);

        APIResponseHandler<APIUserLoginData>* loginCellphone(const QString& cellphone, const QString& password);

        APIResponseHandler<APIUserPrivateMessagesData>*
        userPrivateMessages(const QString& cookieToken, int limit = 30, int offset = 0);

        APIResponseHandler<APIPlaylistCatListData>* playlistCatlist();

        // 精品歌单
        APIResponseHandler<APITopPlayListData>*
        topPlaylistHighQuality(const QString& cat = "全部", int limit = 50, qint64 before = 0);

        // 歌单详情
        APIResponseHandler<APIPlayListDetailData>* playlistDetail(int playlistId);

        // 分类歌单
        APIResponseHandler<APITopPlayListData>* topPlaylist(const QString& cat, int limit = 50, int offset = 0);

        // 电台分类
        APIResponseHandler<APIDJCategoryListData>* djCatList();

        // 歌曲详情
        APIResponseHandler<QString>* songDetail(const QVector<int>& songIds);

        // 歌曲url
        APIResponseHandler<APISongUrlData>* songUrl(SongId songId, SongQuality songQuality = SongQuality::Q990000);

        // 歌手介绍
        APIResponseHandler<QString>* artistDesc(ArtistId artistId);

        static void initInstance();

        static void freeInstance();

        static MusicAPI* instance();
      private:
        static MusicAPI* instance_;
    };
} // namespace MusicPlayer::API

Q_DECLARE_METATYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APIDJBannersData>)
Q_DECLARE_METATYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APIDJCategoryExcludeHotData>)
