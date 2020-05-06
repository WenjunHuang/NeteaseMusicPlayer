//
// Created by HUANG WEN JUN on 2020/5/6.
//
#include "service.h"

namespace MusicPlayer::Service {
    void initServiceModule() {
        PlayListRepository::initInstance();
    }
}