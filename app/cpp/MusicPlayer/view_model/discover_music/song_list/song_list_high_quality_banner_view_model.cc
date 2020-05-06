//
// Created by HUANG WEN JUN on 2019/12/1.
//

#include "song_list_high_quality_banner_view_model.h"
#include "api.h"
#include "util.h"

namespace MusicPlayer::ViewModel {
    using namespace MusicPlayer::API;
    using namespace MusicPlayer::Util;
    void SongListHighQualityBannerViewModel::reload() {
        if (std::get_if<LoadingState>(&_state))
            return;

        setState(LoadingState{});
        auto api    = MusicAPI::instance();
        auto result = api->topPlaylistHighQuality(_categoryName, 1);
        connect(
            result, &APIResponseHandler<APITopPlayListData>::finished, [this](const APIResponse<APITopPlayListData>& result) {
                std::visit(
                    [this](auto& v) {
                        if constexpr (std::is_convertible_v<decltype(v), APITopPlayListData>) {
                            if (v.playlists.length() > 0) {
                                auto& first = v.playlists.first();
                                setState(ReadyState{QVariant::fromValue(
                                    SongListHighQualityBannerReadyData{first.name, first.copywriter, first.coverImgUrl})});
                            } else {
                                setState(ReadyState{});
                            }
                        } else {
                            setState(ErrorState{"error"});
                        }
                    },
                    result);

                return std::nullopt;
            });
    }

    void SongListHighQualityBannerViewModel::registerMetaTypes() { qRegisterMetaType<SongListHighQualityBannerReadyData>(); }
} // namespace MusicPlayer::ViewModel