//
// Created by HUANG WEN JUN on 2019/11/27.
//

#include <thread>
#include <memory>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include "cpu_thread_pool_executor.h"

namespace MusicPlayer::Util{

    std::unique_ptr<folly::Executor> createCPUThreadPoolExecutor() {
        return std::make_unique<folly::CPUThreadPoolExecutor>(std::thread::hardware_concurrency());
    }
}
