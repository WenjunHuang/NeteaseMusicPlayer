//
// Created by HUANG WEN JUN on 2019/11/27.
//

#pragma once
#include <folly/Executor.h>
#include <memory>

namespace MusicPlayer::Util{
    // because Qt5 also defined macro "slots" and folly has a "slots" variable, so if put together will cause compiler treat "slots" as macro :(
    std::unique_ptr<folly::Executor> createCPUThreadPoolExecutor();
}

