//
// Created by HUANG WEN JUN on 2019/11/27.
//

#pragma once

#include <QtCore>
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

        QThread* getHTTPThread();

        QThread* getDBThread();

        QThread* getMainThread();

      private:
        static AppExecutor* _instance;

        QThread* _httpThread;
        QThread* _dbThread;
        QThread* _mainThread;
    };
} // namespace MusicPlayer::Util
