//
// Created by rick on 2020/3/22.
//

#pragma once
#include <QtCore/QObject>
#include <filesystem>

namespace MusicPlayer::Repository {
    namespace fs = std::filesystem;
    class AppConfig:public QObject {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(AppConfig)
        AppConfig();
      public:
        fs::path imageCacheDir() const;
      public:
        static void initInstance();
        static void freeInstance();
        static AppConfig* instance();

      private:
        static AppConfig* instance_;
    };
}
