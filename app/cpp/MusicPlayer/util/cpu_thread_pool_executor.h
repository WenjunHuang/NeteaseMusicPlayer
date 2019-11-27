//
// Created by HUANG WEN JUN on 2019/11/27.
//

#pragma once
#include <folly/Executor.h>
#include <memory>

namespace MusicPlayer::Util{
    // because Qt5 also defined macro slots, and folly use this variable :(
    std::shared_ptr<folly::Executor> createCPUThreadPoolExecutor();
}

