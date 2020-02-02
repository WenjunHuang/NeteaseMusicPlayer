//
// Created by rick on 2019/12/15.
//

#pragma once

#include "tables.h"
#include <QtCore>
#include <folly/futures/Future.h>
#include <memory>
#include <optional>
#include <vector>

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

        // 播放列表
        SemiFuture<Unit> replacePlayListSongs(std::vector<TPlayListSong>&& songs);
        SemiFuture<std::vector<TPlayListSong>> getAllPlayListSongs();

        // 图片缓存
        SemiFuture<TImageCache> insertImageCache(TImageCache imageCache);
        SemiFuture<Unit> updateImageCache(TImageCache imageCache);
        SemiFuture<std::optional<TImageCache>> getImageCacheByUrl(QString url);
        SemiFuture<std::vector<TImageCache>> getAllImageCaches();
        SemiFuture<std::vector<TImageCache>> getImageCachesOverCapacity(int capacity);
        SemiFuture<std::vector<TImageCache>> getOldImageCaches(int maxAgeInMilliseconds);

      private:
        static DatabaseRepository* _instance;
        QString _dbFilePath;
    };
} // namespace MusicPlayer::Repository
