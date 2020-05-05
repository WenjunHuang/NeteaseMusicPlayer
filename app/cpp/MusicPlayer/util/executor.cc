//
// Created by HUANG WEN JUN on 2019/11/27.
//

#include "executor.h"
#include <memory>
namespace MusicPlayer::Util {

    AppExecutor* AppExecutor::_instance = nullptr;

    AppExecutor::AppExecutor() {
        // qt的主线程
        _mainThread = qApp->thread();

        // qt的http线程
        _httpThread = new QThread(this);
        _httpThread->setObjectName(QStringLiteral("HTTP Thread"));
        _httpThread->start();

        // db 线程
        _dbThread = new QThread(this);
        _dbThread->setObjectName(QStringLiteral("DB Thread"));
        _dbThread->start();
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

    QThread* AppExecutor::getHTTPThread() { return _httpThread; }

    QThread* AppExecutor::getDBThread() { return _dbThread; }
    QThread* AppExecutor::getMainThread() { return _mainThread; }

} // namespace MusicPlayer::Util
