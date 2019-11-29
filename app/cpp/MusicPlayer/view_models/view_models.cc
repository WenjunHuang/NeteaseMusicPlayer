//
// Created by HUANG WEN JUN on 2019/11/29.
//

#include "view_models.h"
#include "song_category_list_view_model.h"

namespace MusicPlayer::ViewModels{
    void registerMetaTypes(){
        qRegisterMetaType<UnInitState>();
        qRegisterMetaType<LoadingState>();
        qRegisterMetaType<ErrorState>();
        qRegisterMetaType<ReadyStateItem>();
        qRegisterMetaType<ReadyState>();
    }
}