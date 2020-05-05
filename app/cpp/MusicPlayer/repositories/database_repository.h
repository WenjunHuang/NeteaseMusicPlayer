//
// Created by rick on 2019/12/15.
//

#pragma once

#include <QtCore>
#include <memory>
#include <optional>
#include <vector>
#include <variant>

#include "tables.h"
#include "wobjectdefs.h"
#include "database_response.h"

namespace MusicPlayer::Repository {
    using namespace sqlite_orm;

    class DatabaseRepository : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(DatabaseRepository)
        DatabaseRepository();

      public:
        static void initInstance();
        static void freeInstance();
        static DatabaseRepository* instance();

        // 播放列表
        DatabaseResponseHandler<int>* replacePlayListSongs(QVector<TPlayListSong>&& songs);
        DatabaseResponseHandler<QVector<TPlayListSong>>* getAllPlayListSongs();

        // 图片缓存
        DatabaseResponseHandler<int>* insertImageCache(TImageCache imageCache);
        DatabaseResponseHandler<int>* updateImageCache(TImageCache imageCache);
        DatabaseResponseHandler<std::optional<TImageCache>>* getImageCacheByUrl(QString url);
        DatabaseResponseHandler<QVector<TImageCache>>* getAllImageCaches();
        DatabaseResponseHandler<QVector<TImageCache>>* getImageCachesOverCapacity(int capacity);
        DatabaseResponseHandler<QVector<TImageCache>>* getOldImageCaches(int maxAgeInMilliseconds);

        bool event(QEvent* event) override;
      private:
        static DatabaseRepository* _instance;
        QString _dbFilePath;
    };
} // namespace MusicPlayer::Repository
