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

namespace MusicPlayer::Repository {
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

      private:
        folly::SemiFuture<Response<APIPlaylistCatListData>> getPlaylistCatListData();

        std::optional<APIPlaylistCatListData> _categoryData;

        // if is loading
        std::optional<folly::Future<void>> _loading;

        std::vector<folly::Promise<Response<APIPlaylistCatListData>>> _waitings;

        static SongCategoryRepository* _instance;
    };
} // namespace MusicPlayer::Repository
