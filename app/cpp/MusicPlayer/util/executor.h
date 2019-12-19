//
// Created by HUANG WEN JUN on 2019/11/27.
//

#pragma once

#include <QtCore>
#include <folly/Executor.h>
#include <memory>
namespace MusicPlayer::Util {
    class AppExecutor : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY(AppExecutor)
        AppExecutor();

      public:
        static void initInstance();

        static void freeInstance();

        static AppExecutor* instance();

        // folly的cpu thread pool executor，与qt无关
        std::shared_ptr<folly::Executor> getCPUExecutor();

        // 一个固定的qt QThread作为qt http线程
        std::shared_ptr<folly::Executor> getHTTPExecutor();

        // 固定的qt thread作为sqlite3操作线程
        std::shared_ptr<folly::Executor> getDBExecutor();

        // qt主线程executor
        std::shared_ptr<folly::Executor> getMainExecutor();

        QThread* getHTTPThread();
        QThread* getDBThread();

      private:
        static AppExecutor* _instance;
        std::shared_ptr<folly::Executor> _cpuExecutor;
        std::shared_ptr<folly::Executor> _httpExecutor;
        std::shared_ptr<folly::Executor> _dbExecutor;
        std::shared_ptr<folly::Executor> _mainExecutor;

        QThread* _httpThread;
        QThread* _dbThread;
        QThread* _mainThread;
    };

    inline folly::Executor* mainExecutor() { return AppExecutor::instance()->getMainExecutor().get(); }

    inline folly::Executor* httpExecutor() { return AppExecutor::instance()->getHTTPExecutor().get(); }

    inline folly::Executor* cpuExecutor() { return AppExecutor::instance()->getCPUExecutor().get(); }

    inline folly::Executor* dbExecutor() { return AppExecutor::instance()->getDBExecutor().get(); }

    class QtExecutorEventWorker : public QObject {
        Q_OBJECT
      public:
        QtExecutorEventWorker();

      protected:
        bool event(QEvent* ev) override;
    };
} // namespace MusicPlayer::Util
