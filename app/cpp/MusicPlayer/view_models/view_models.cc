//
// Created by HUANG WEN JUN on 2019/11/29.
//

#include "view_models.h"
#include "discover_music/song_list/song_category_list_view_model.h"

namespace MusicPlayer::ViewModels{
    void registerMetaTypes(){
        StateKinds::registerMetaTypes();
        SongCategoryListViewModel::registerMetaTypes();
        SongListHighQualityBannerViewModel::registerMetaTypes();
        SongCategoryPlayListsViewModel::registerMetaTypes();
    }
}