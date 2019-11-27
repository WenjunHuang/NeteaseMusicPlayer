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
        QtExecutorEvent(folly::Func&& func)
            : QEvent{(QEvent::Type)kEventType}, _func{std::move(func)} {}

        void runNow() { _func(); }

      private:
        folly::Func _func;
    };

    class QtExecutor : public folly::Executor {

      public:
        QtExecutor(QObject* worker) : _worker{worker} {}

        void add(folly::Func func) {
            QCoreApplication::postEvent(_worker,
                                        new QtExecutorEvent(std::move(func)));
        }

      private:
        QObject* _worker;
    };

    QtExecutorEventWorker::QtExecutorEventWorker() {}

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
        _mainThread     = qApp->thread();
        auto mainWorker = new QtExecutorEventWorker;
        mainWorker->moveToThread(_mainThread);
        _mainExecutor = std::make_shared<QtExecutor>(mainWorker);

        // qt的io线程
        _ioThread = new QThread(this);
        _ioThread->setObjectName(QLatin1Literal("IO Thread"));
        auto ioWorker = new QtExecutorEventWorker;
        ioWorker->moveToThread(_ioThread);
        _ioExecutor =
            std::make_shared<QtExecutor>(ioWorker); // folly::getIOExecutor();
        _ioThread->start();

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
    std::shared_ptr<folly::Executor> AppExecutor::getCPUExecutor() {
        return _cpuExecutor;
    }
    std::shared_ptr<folly::Executor> AppExecutor::getIOExecutor() {
        return _ioExecutor;
    }
    std::shared_ptr<folly::Executor> AppExecutor::getMainExecutor() {
        return _mainExecutor;
    }
    QThread* AppExecutor::getIOThread() { return _ioThread; }

} // namespace MusicPlayer::Util
