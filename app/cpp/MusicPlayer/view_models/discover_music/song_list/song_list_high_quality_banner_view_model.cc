//
// Created by HUANG WEN JUN on 2019/12/1.
//

#include "song_list_high_quality_banner_view_model.h"
#include "../../../api/api.h"
#include "../../../util/util.h"

namespace MusicPlayer::ViewModels {
    using namespace MusicPlayer::API;
    using namespace MusicPlayer::Util;
    void SongListHighQualityBannerViewModel::reload() {
        if (_loading && !_loading->isReady())
            return;

        setState(LoadingState{});
        MusicAPI api;
        _loading = api.topPlaylistHighQuality(_categoryName, 1)
                       .via(mainExecutor())
                       .thenValue([this](Response<APITopPlayListData>&& result) {
                           std::visit(
                               [this](auto& v) {
                                   if constexpr (std::is_convertible_v<decltype(v), APITopPlayListData>) {
                                       if (v.playlists.length() > 0) {
                                           auto& first = v.playlists.first();
                                           setState(ReadyState{QVariant::fromValue(SongListHighQualityBannerReadyData{
                                               first.name,
                                               first.copywriter,
                                               first.coverImgUrl
                                           })});
                                       } else {
                                           setState(ReadyState{QVariant()});
                                       }
                                   }else {
                                       setState(ErrorState{"error"});
                                   }
                               },
                               result);

                           return std::nullopt;
                       });
    }


    void SongListHighQualityBannerViewModel::registerMetaTypes() {
        qRegisterMetaType<SongListHighQualityBannerReadyData>();
    }
} // namespace MusicPlayer::ViewModels