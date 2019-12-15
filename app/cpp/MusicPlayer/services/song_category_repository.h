//
// Created by rick on 2019/11/13.
//

#pragma once
#include "../api/api.h"
#include "../util/executor.h"
#include <QtCore>
#include <folly/futures/Future.h>
#include <optional>
#include <type_traits>
#include <variant>
#include <vector>

namespace MusicPlayer::Service {
    using namespace MusicPlayer::API;
    using namespace MusicPlayer::Util;

    class SongCategoryRepository : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(SongCategoryRepository)
        SongCategoryRepository() {}

      public:
        static void initInstance();

        static void freeInstance();

        static SongCategoryRepository* instance();

        folly::SemiFuture<Response<APIPlaylistCatListData>> getPlaylistCatListData();

      private:

        std::optional<APIPlaylistCatListData> _categoryData;

        // if is loading
        std::optional<folly::Future<std::nullopt_t>> _loading;

        std::vector<folly::Promise<Response<APIPlaylistCatListData>>> _waitings;

        static SongCategoryRepository* _instance;
    };
} // namespace MusicPlayer::Repository
