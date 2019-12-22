//
// Created by rick on 2019/12/15.
//

#pragma once

#include "tables.h"
#include <QtCore>
#include <folly/futures/Future.h>
#include <vector>
#include <memory>

namespace MusicPlayer::Repository {
    using namespace sqlite_orm;
    using namespace folly;
    class DatabaseRepository : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(DatabaseRepository)
        DatabaseRepository();

      public:
        static void initInstance();
        static void freeInstance();
        static DatabaseRepository* instance();

        SemiFuture<Unit> replacePlayListSongs(std::vector<TPlayListSong>&& songs);
        SemiFuture<std::vector<TPlayListSong>> getAllPlayListSongs();

      private:
        static DatabaseRepository* _instance;
        QString _dbFilePath;
    };
} // namespace MusicPlayer::Repository
