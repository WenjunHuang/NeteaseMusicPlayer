//
// Created by rick on 2020/5/5.
//

#pragma once
#include "http.h"
#include "wobjectdefs.h"
#include "wobjectimpl.h"
#include "error.h"
#include "data/data.h"
#include <variant>

namespace MusicPlayer::API {
    template <typename T> using APIResponse = std::variant<APIError, T>;
    template <typename T> class APIResponseHandler : public QObject {
        W_OBJECT(APIResponseHandler)
      public:
        explicit APIResponseHandler(QObject* parent = nullptr) : QObject{parent} {}

        void finished(const APIResponse<T>& result) W_SIGNAL(finished, result)
    };
}
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APIBannersData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APIDJBannersData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APIDJCategoryExcludeHotData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APIDJCategoryRecommendData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APIDJCategoryListData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APIPersonalizedData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APIPersonalizedNewSongData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APIPlaylistCatListData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APIPlayListDetailData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APISongPrivilegeData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APISongUrlData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APITopPlayListData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APIUserLoginData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<MusicPlayer::API::APIUserPrivateMessagesData>)
W_REGISTER_ARGTYPE(MusicPlayer::API::APIResponse<QString>)
W_OBJECT_IMPL_INLINE(MusicPlayer::API::APIResponseHandler<T>, template <typename T>)
