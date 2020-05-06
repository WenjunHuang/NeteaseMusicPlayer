//
// Created by HUANG WEN JUN on 2019/12/3.
//

#include "song_category_play_lists_view_model.h"
#include "api.h"
#include "util.h"
#include <type_traits>

namespace MusicPlayer::ViewModel {
    using namespace MusicPlayer::API;
    using namespace MusicPlayer::Util;

    SongCategoryPlayListsViewModel::CreatorType creatorType(const APIPlayListDetailUser& user) {
        if (user.userType == 2)
            return SongCategoryPlayListsViewModel::CreatorType::Official;
        if (user.userType == 4)
            return SongCategoryPlayListsViewModel::CreatorType::Musician;
        if (!user.expertTags.empty())
            return SongCategoryPlayListsViewModel::CreatorType::Expert;

        return SongCategoryPlayListsViewModel::CreatorType::Normal;
    }

    void SongCategoryPlayListsViewModel::load(const QString& catName, int limit, int offset) {
        if (auto ptr = std::get_if<LoadingState>(&_state)) {
            return;
        } else {
            auto api = MusicAPI::instance();
            setState(LoadingState{});
            auto response = api->topPlaylist(catName, limit, offset);
            connect(response,
                    &APIResponseHandler<APITopPlayListData>::finished,
                    [this](const APIResponse<APITopPlayListData>& response) {
                        std::visit(
                            [this](const auto& value) {
                                if constexpr (std::is_convertible_v<decltype(value), APITopPlayListData>) {
                                    QVariantList playlists;
                                    for (const auto& playlist : value.playlists) {
                                        playlists.append(QVariant::fromValue(
                                            SongCategoryPlayListsViewModelPlaylistItem{playlist.id,
                                                                                       playlist.coverImgUrl,
                                                                                       playlist.name,
                                                                                       playlist.playCount,
                                                                                       playlist.creator.nickname,
                                                                                       creatorType(playlist.creator)}));
                                    }
                                    setState(ReadyState{QVariant::fromValue(
                                        SongCategoryPlayListsViewModelReadyStateData{playlists, value.total})});
                                } else {
                                    setState(ErrorState{apiErrorMessage(value)});
                                }
                            },
                            response);
                    });
        }
    }
    void SongCategoryPlayListsViewModel::registerMetaTypes() {
        qRegisterMetaType<SongCategoryPlayListsViewModelReadyStateData>();
        qRegisterMetaType<SongCategoryPlayListsViewModelPlaylistItem>();
    }
} // namespace MusicPlayer::ViewModel
