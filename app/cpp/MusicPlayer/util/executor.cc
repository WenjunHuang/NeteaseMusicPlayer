//
// Created by HUANG WEN JUN on 2019/11/27.
//

#include "executor.h"
#include "cpu_thread_pool_executor.h"
#include <memory>
namespace MusicPlayer::Util {
    const int kEventType = QEvent::registerEventType();

    class QtExecutorEvent : public QEvent {
      public:
        explicit QtExecutorEvent(folly::Func&& func) : QEvent{(QEvent::Type)kEventType}, _func{std::move(func)} {}

        void runNow() { _func(); }

      private:
        folly::Func _func;
    };

    class QtExecutor : public folly::Executor {

      public:
        explicit QtExecutor(QThread* thread) {
            _worker = new QtExecutorEventWorker;
            _worker->moveToThread(thread);
        }

        void add(folly::Func func) override { QCoreApplication::postEvent(_worker, new QtExecutorEvent(std::move(func))); }

      private:
        QObject* _worker;
    };

    bool QtExecutorEventWorker::event(QEvent* ev) {
        if (ev->type() == kEventType) {
            auto executorEvent = dynamic_cast<QtExecutorEvent*>(ev);
            executorEvent->runNow();
            return true;
        }

        return QObject::event(ev);
    }

    AppExecutor* AppExecutor::_instance = nullptr;

    AppExecutor::AppExecutor() {
        // qt的主线程
        _mainThread   = qApp->thread();
        _mainExecutor = std::make_unique<QtExecutor>(_mainThread);

        // qt的http线程
        _httpThread = new QThread(this);
        _httpThread->setObjectName(QStringLiteral("HTTP Thread"));
        _httpExecutor = std::make_unique<QtExecutor>(_httpThread);
        _httpThread->start();

        // db 线程
        _dbThread = new QThread(this);
        _dbThread->setObjectName(QStringLiteral("DB Thread"));
        _dbExecutor = std::make_unique<QtExecutor>(_dbThread);
        _dbThread->start();

        // cpu线程池
        _cpuExecutor = createCPUThreadPoolExecutor();
    }

    void AppExecutor::initInstance() {
        if (_instance == nullptr) {
            _instance = new AppExecutor;
        }
    }

    void AppExecutor::freeInstance() {
        if (_instance != nullptr) {
            delete _instance;
            _instance = nullptr;
        }
    }

    AppExecutor* AppExecutor::instance() { return _instance; }
    folly::Executor* AppExecutor::getCPUExecutor() { return _cpuExecutor.get(); }
    folly::Executor* AppExecutor::getHTTPExecutor() { return _httpExecutor.get(); }
    folly::Executor* AppExecutor::getMainExecutor() { return _mainExecutor.get(); }
    folly::Executor* AppExecutor::getDBExecutor() { return _dbExecutor.get(); }

    QThread* AppExecutor::getHTTPThread() { return _httpThread; }

} // namespace MusicPlayer::Util
