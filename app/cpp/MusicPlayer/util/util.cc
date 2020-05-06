//
// Created by HUANG WEN JUN on 2020/5/6.
//
#include "util.h"
namespace MusicPlayer::Util {
    void initUtilModule() {
        Logger::initInstance();
        AppExecutor::initInstance();
    }
}