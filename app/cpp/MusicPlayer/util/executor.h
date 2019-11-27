//
// Created by HUANG WEN JUN on 2019/11/27.
//

#pragma once

#include <QtCore>
#include <memory>
#include <folly/Executor.h>
namespace MusicPlayer::Util {
    class AppExecutor : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY(AppExecutor)
        AppExecutor();

      public:
        static void initInstance();

        static void freeInstance();

        static AppExecutor* instance();

        // 使用folly的cpu thread pool executor，与qt无关
        std::shared_ptr<folly::Executor> getCPUExecutor();

        // 使用一个固定的qt QThread作为io线程，因为qt的http库
        std::shared_ptr<folly::Executor> getIOExecutor();

        // qt主线程executor
        std::shared_ptr<folly::Executor> getMainExecutor();

        QThread* getIOThread();

      private:
        static AppExecutor* _instance;
        std::shared_ptr<folly::Executor> _cpuExecutor;
        std::shared_ptr<folly::Executor> _ioExecutor;
        std::shared_ptr<folly::Executor> _mainExecutor;

        QThread *_ioThread;
        QThread *_mainThread;
    };


    class QtExecutorEventWorker: public QObject {
      Q_OBJECT
      public:
        QtExecutorEventWorker();
      protected:
        bool event(QEvent* ev) override;
    };
} // namespace MusicPlayer::Util
