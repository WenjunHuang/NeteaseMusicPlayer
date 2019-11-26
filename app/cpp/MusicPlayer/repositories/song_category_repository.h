//
// Created by rick on 2019/11/13.
//

#pragma once
#include "../api/api.h"
#include "../api/data/playlist_catlist.h"
#include "../asyncfuture.h"
#include <QtCore>
#include <optional>
#include <type_traits>
#include <variant>

namespace MusicPlayer::Repository {
    using namespace MusicPlayer::API;

    class SongCategoryRepository : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(SongCategoryRepository)
        SongCategoryRepository() {}

      public:
      public:
        static void initInstance();

        static void freeInstance();

        static SongCategoryRepository* instance();

      private:
        QFuture<Response<APIPlaylistCatListData>>
        asyncGetPlaylistCatListData() {
            QFutureInterface<Response<APIPlaylistCatListData>> promise;
            if (_categoryData) {
                // 已经有缓存了
                Response<APIPlaylistCatListData> r = _categoryData.value();
                promise.reportFinished(&r);
                return promise.future();
            } else {
                // 没有缓存
                // 看看有没正在执行的api调用
                if (_loading) {
                    // 有，那么等它完成
                    return AsyncFuture::observe(_loading.value())
                        .subscribe(
                            [](Response<APIPlaylistCatListData> response) {
                                return response;
                            })
                        .future();
                } else {
                    // 还没有，那么我们创建它
                    MusicAPI api;
                    _loading = AsyncFuture::observe(api.playlistCatlist())
                            .subscribe(
                                [this](
                                    Response<APIPlaylistCatListData> response) {
                                    std::visit(
                                        [this](const auto& var) {
                                            if constexpr (
                                                std::is_convertible_v<
                                                    decltype(var),
                                                    APIPlaylistCatListData>) {
                                                _categoryData = var;
                                            } else {
                                                //todo 记录日志
                                            }

                                            return var;
                                        },
                                        response);
                                    return response;
                                })
                            .future();
                }
            }
        }

        std::optional<APIPlaylistCatListData> _categoryData;

        // if is loading
        std::optional<APIResponse<APIPlaylistCatListData>> _loading;

        static SongCategoryRepository* _instance;
    };
} // namespace MusicPlayer::Repository
