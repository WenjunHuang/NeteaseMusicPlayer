//
// Created by rick on 2019/11/13.
//

#include "song_category_repository.h"
#include <variant>

namespace MusicPlayer::Repository {
    SongCategoryRepository* SongCategoryRepository::_instance = nullptr;
    void SongCategoryRepository::initInstance() {
        if (!_instance)
            _instance = new SongCategoryRepository;
    }
    void SongCategoryRepository::freeInstance() {
        if (_instance) {
            delete _instance;
            _instance = nullptr;
        }
    }

    SongCategoryRepository* SongCategoryRepository::instance() { return _instance; }

    folly::SemiFuture<Response<APIPlaylistCatListData>> SongCategoryRepository::getPlaylistCatListData() {
        folly::Promise<Response<APIPlaylistCatListData>> promise;
        auto result = promise.getSemiFuture();
        if (_categoryData) {
            // 已经有缓存了
            promise.setValue(_categoryData.value());
        } else {
            // 没有缓存
            if (_loading && !_loading->isReady()) {
                _waitings.push_back(std::move(promise));
            } else {
                MusicAPI api;
                _waitings.push_back(std::move(promise));
                _loading = api.playlistCatlist()
                               .via(AppExecutor::instance()->getMainExecutor().get())
                               .thenValue([this](Response<APIPlaylistCatListData>&& response) {
                                   std::visit(
                                       [this](auto& var) {
                                           if constexpr (std::is_convertible_v<decltype(var), APIPlaylistCatListData>) {
                                               _categoryData = var;
                                           } else {
                                               // todo 记录日志
                                           }
                                       },
                                       response);

                                   std::for_each(
                                       _waitings.begin(), _waitings.end(), [&](auto& promise) { promise.setValue(response); });
                                   _waitings.clear();

                                   return std::nullopt;
                               });
            }
        }
        return result;
    }
} // namespace MusicPlayer::Repository
