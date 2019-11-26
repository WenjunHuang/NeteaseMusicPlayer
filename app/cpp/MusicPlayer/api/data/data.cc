//
// Created by HUANG WEN JUN on 2019/11/26.
//
#include "data.h"

namespace MusicPlayer::API {
    void registerMetaTypes() {
        qRegisterMetaType<APIBannerData>();
        qRegisterMetaType<APIBannersData>();
        qRegisterMetaType<APIDJBannerData>();
        qRegisterMetaType<APIDJBannersData>();
        qRegisterMetaType<APIDJCategoryItemData>();
        qRegisterMetaType<APIDJCategoryExcludeHotData>();
        qRegisterMetaType<APIDJCategoryRecommendData>();
        qRegisterMetaType<APIDJCategoryRecommendItemData>();
        qRegisterMetaType<APIDJCategoryRecommendItemRadioData>();
        qRegisterMetaType<APIPersonalizedItemData>();
        qRegisterMetaType<APIPersonalizedData>();

        qRegisterMetaType<APIPersonalizedNewSongResultSongAlbumData>();
        qRegisterMetaType<APIPersonalizedNewSongResultSongArtistData>();
        qRegisterMetaType<APIPersonalizedNewSongResultSongData>();
        qRegisterMetaType<APIPersonalizedNewSongResultData>();
        qRegisterMetaType<APIPersonalizedNewSongData>();

        qRegisterMetaType<APISongPrivilegeData>();

        qRegisterMetaType<APIUserAccountData>();
        qRegisterMetaType<APIUserProfileData>();
        qRegisterMetaType<APIUserLoginData>();

        qRegisterMetaType<APIUserPrivateMessageData>();
        qRegisterMetaType<APIUserPrivateMessagesData>();
        qRegisterMetaType<APIUserPrivateMessageUserData>();
    }
} // namespace MusicPlayer::API
