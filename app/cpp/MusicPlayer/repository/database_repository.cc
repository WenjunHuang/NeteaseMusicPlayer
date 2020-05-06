//
// Created by rick on 2019/12/15.
//

#include "database_repository.h"
#include "sqlite_orm.h"
#include "tables.h"
#include "util.h"
#include <QtCore>
#include <functional>
#include <iostream>

namespace MusicPlayer::Repository {
    using namespace sqlite_orm;
    using namespace MusicPlayer::Util;

    const int kInitDatabaseRepositoryEventType = QEvent::registerEventType();
    const int kDatabaseActionEventType         = QEvent::registerEventType();

    struct DatabaseActionEvent : public QEvent {
        DatabaseActionEvent(std::function<void()>&& a)
            : QEvent{(QEvent::Type)(kDatabaseActionEventType)}, action{std::move(a)} {}
        std::function<void()> action;
    };

    static auto getStorage(QString& filePath) {
        return make_storage(filePath.toStdString(), TPlayListSong::table(), TImageCache::table());
    }

    DatabaseRepository* DatabaseRepository::_instance = nullptr;
    void DatabaseRepository::initInstance() {
        if (_instance)
            return;

        _instance = new DatabaseRepository();
    }

    void DatabaseRepository::freeInstance() {
        if (_instance) {
            delete _instance;
            _instance = nullptr;
        }
    }

    DatabaseRepository* DatabaseRepository::instance() { return _instance; }

    DatabaseRepository::DatabaseRepository() {
        //        _dbFilePath = QStandardPaths::locate(QStandardPaths::AppDataLocation, "database.sqlite",
        //        QStandardPaths::LocateFile);
        auto dbThread = Util::AppExecutor::instance()->getDBThread();
        moveToThread(dbThread);
        QCoreApplication::postEvent(this, new QEvent((QEvent::Type)kInitDatabaseRepositoryEventType));
    }

    bool DatabaseRepository::event(QEvent* event) {
        if (event->type() == kInitDatabaseRepositoryEventType) {
            _dbFilePath  = "database.sqlite";
            auto storage = getStorage(_dbFilePath);
            storage.sync_schema();

            return true;
        } else if (event->type() == kDatabaseActionEventType) {
            auto actionEvent = dynamic_cast<DatabaseActionEvent*>(event);
            actionEvent->action();
            return true;
        } else
            return QObject::event(event);
    }

    DatabaseResponseHandler<int>* DatabaseRepository::replacePlayListSongs(QVector<TPlayListSong>&& songs) {
        auto response = new DatabaseResponseHandler<int>;
        connect(response, &DatabaseResponseHandler<int>::finished, &QObject::deleteLater);
        QCoreApplication::postEvent(this, new DatabaseActionEvent{[this, response, songs = std::move(songs)]() {
                                        int batchSize = 10;
                                        auto storage  = getStorage(_dbFilePath);
                                        storage.begin_transaction();
                                        try {
                                            storage.remove_all<TPlayListSong>();
                                            auto start = songs.cbegin();
                                            int count  = 0;
                                            for (auto index = songs.cbegin(); index < songs.cend(); index++) {
                                                if (count != 0 && (count % batchSize) == 0) {
                                                    storage.insert_range(start, index);
                                                    start = index;
                                                }
                                                count++;
                                            }
                                            if (start < songs.cend())
                                                storage.insert_range(start, songs.cend());
                                            storage.commit();
                                            emit response->finished(count);
                                        } catch (const std::exception& e) {
                                            storage.rollback();
                                            emit response->finished(QString(e.what()));
                                        }
                                    }});
        return response;
    }

    DatabaseResponseHandler<QVector<TPlayListSong>>* DatabaseRepository::getAllPlayListSongs() {
        auto response = new DatabaseResponseHandler<QVector<TPlayListSong>>;
        connect(response, &DatabaseResponseHandler<QVector<TPlayListSong>>::finished, &QObject::deleteLater);
        QCoreApplication::postEvent(this, new DatabaseActionEvent{[this, response]() {
                                        try {
                                            auto storage = getStorage(_dbFilePath);
                                            auto result  = storage.get_all<TPlayListSong, QVector<TPlayListSong>>(
                                                order_by(&TPlayListSong::songId));
                                            emit response->finished(result);
                                        } catch (std::exception& error) { emit response->finished(QString(error.what())); }
                                        //            std::vector<TPlayListSong> result;
                                        //            for (auto &song:
                                        //            storage.iterate<TPlayListSong>(order_by(&TPlayListSong::songId))) {
                                        //                result.push_back(song);
                                        //            }
                                        //
                                        //            return result;
                                    }});
        return response;
    }

    DatabaseResponseHandler<int>* DatabaseRepository::insertImageCache(TImageCache imageCache) {
        auto handler = new DatabaseResponseHandler<int>;
        connect(handler, &DatabaseResponseHandler<int>::finished, &QObject::deleteLater);
        QCoreApplication::postEvent(this, new DatabaseActionEvent{[this, handler, imageCache]() {
                                        try {
                                            auto storage = getStorage(_dbFilePath);
                                            auto result  = storage.insert<TImageCache>(imageCache);
                                            emit handler->finished(result);
                                        } catch (std::exception& error) { emit handler->finished(QString(error.what())); }
                                    }});
        return handler;
        //        return SemiFuture<Unit>().via(dbExecutor()).thenValue([this, imageCache = std::move(imageCache)](Unit u)
        //        mutable {
        //            auto storage  = getStorage(_dbFilePath);
        //            auto newId    = storage.insert(imageCache);
        //            imageCache.id = newId;
        //            return imageCache;
        //        });
    }
    DatabaseResponseHandler<std::optional<TImageCache>>* DatabaseRepository::getImageCacheByUrl(QString url) {
        auto handler = new DatabaseResponseHandler<std::optional<TImageCache>>;
        connect(handler, &DatabaseResponseHandler<std::optional<TImageCache>>::finished, &QObject::deleteLater);
        QCoreApplication::postEvent(this, new DatabaseActionEvent{[this, handler, url]() {
                                        try {
                                            auto storage = getStorage(_dbFilePath);
                                            auto result =
                                                storage.get_all<TImageCache>(where(c(&TImageCache::url) == url.toStdString()));
                                            if (result.empty())
                                                emit handler->finished(std::nullopt);
                                            else
                                                emit handler->finished(result.at(0));
                                        } catch (std::exception& error) { emit handler->finished(QString(error.what())); }
                                    }});
        return handler;
    }
    DatabaseResponseHandler<QVector<TImageCache>>* DatabaseRepository::getAllImageCaches() { return nullptr; }
    DatabaseResponseHandler<QVector<TImageCache>>* DatabaseRepository::getImageCachesOverCapacity(int capacity) {
        return nullptr;
    }
    DatabaseResponseHandler<QVector<TImageCache>>* DatabaseRepository::getOldImageCaches(int maxAgeInMilliseconds) {
        return nullptr;
    }

} // namespace MusicPlayer::Repository