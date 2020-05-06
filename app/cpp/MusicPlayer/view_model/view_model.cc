//
// Created by HUANG WEN JUN on 2019/11/29.
//

#include "view_model.h"
#include <QtQml>

namespace MusicPlayer::ViewModel{
    void registerMetaTypes(){
        StateKinds::registerMetaTypes();
        SongCategoryListViewModel::registerMetaTypes();
        SongListHighQualityBannerViewModel::registerMetaTypes();
        SongCategoryPlayListsViewModel::registerMetaTypes();
        DJBannerViewModel::registerMetaTypes();
        BannerViewModel::registerMetaTypes();
    }

    void initViewModelModule() {
        registerMetaTypes();

        qmlRegisterUncreatableType<ViewModel::StateKinds>("MusicPlayer", 1, 0, "StateKinds", "Uncreateable");
        qmlRegisterType<ViewModel::BannerViewModel>("MusicPlayer", 1, 0, "BannerViewModel");
        qmlRegisterType<ViewModel::PersonalizedNewSongViewModel>("MusicPlayer", 1, 0, "PersonalizedNewSongViewModel");
        qmlRegisterType<ViewModel::RecommendationSongListsViewModel>("MusicPlayer", 1, 0, "RecommendationSongListsViewModel");
        qmlRegisterType<ViewModel::SongCategoryListViewModel>("MusicPlayer", 1, 0, "SongCategoryListViewModel");
        qmlRegisterType<ViewModel::SongListHighQualityBannerViewModel>(
            "MusicPlayer", 1, 0, "SongListHighQualityBannerViewModel");
        qmlRegisterType<ViewModel::SongCategoryPlayListsViewModel>("MusicPlayer", 1, 0, "SongCategoryPlayListsViewModel");
        qmlRegisterType<ViewModel::DJBannerViewModel>("MusicPlayer", 1, 0, "DJBannerViewModel");
    }
}