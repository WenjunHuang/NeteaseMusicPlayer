//
// Created by HUANG WEN JUN on 2020/5/6.
//
#include "api.h"

namespace MusicPlayer::API {
    static void registerMetaTypes() {
        qRegisterMetaType<HttpMethod>("MusicPlayer::API::HttpMethod");
        qRegisterMetaType<RequestOption>("MusicPlayer::API::RequestOption");
        qRegisterMetaType<APIResponse<APIBannersData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APIBannersData>");
        qRegisterMetaType<APIResponse<APIDJBannersData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APIDJBannersData>");
        qRegisterMetaType<APIResponse<APIDJCategoryExcludeHotData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APIDJCategoryExcludeHotData>");
        qRegisterMetaType<APIResponse<APIDJCategoryRecommendData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APIDJCategoryRecommendData>");
        qRegisterMetaType<APIResponse<APIDJCategoryListData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APIDJCategoryListData>");
        qRegisterMetaType<APIResponse<APIPersonalizedData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APIPersonalizedData>");
        qRegisterMetaType<APIResponse<APIPersonalizedNewSongData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APIPersonalizedNewSongData>");
        qRegisterMetaType<APIResponse<APIPlaylistCatListData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APIPlaylistCatListData>>");
        qRegisterMetaType<APIResponse<APIPlayListDetailData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APIPlayListDetailData>");
        qRegisterMetaType<APIResponse<APISongPrivilegeData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APISongPrivilegeData>");
        qRegisterMetaType<APIResponse<APISongUrlData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APISongUrlData>");
        qRegisterMetaType<APIResponse<APITopPlayListData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APITopPlayListData>");
        qRegisterMetaType<APIResponse<APIUserLoginData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APIUserLoginData>");
        qRegisterMetaType<APIResponse<APIUserPrivateMessagesData>> ("MusicPlayer::API::APIResponse<MusicPlayer::API::APIUserPrivateMessagesData>");
        qRegisterMetaType<APIResponse<QString>> ("MusicPlayer::API::APIResponse<QString>>");
    }

    void initAPIModule() {
        registerMetaTypes();

        MusicHttpWorker::initInstance();
        MusicAPI::initInstance();
    }
} // namespace MusicPlayer::API