//
// Created by HUANG WEN JUN on 2019/11/27.
//

#include <thread>
#include <memory>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include "cpu_thread_pool_executor.h"

namespace MusicPlayer::Util{

    std::shared_ptr<folly::Executor> createCPUThreadPoolExecutor() {
        return std::make_shared<folly::CPUThreadPoolExecutor>(std::thread::hardware_concurrency());
    }
}
