//
// Created by rick on 2019/12/15.
//

#include "database_repository.h"
#include "../util/sqlite_orm.h"
#include "../util/util.h"
#include "tables.h"
#include <QtCore>
#include <iostream>

namespace MusicPlayer::Repository {
    using namespace sqlite_orm;
    using namespace MusicPlayer::Util;

    static auto getStorage(QString& filePath) { return make_storage(filePath.toStdString(), TPlayListSong::table()); }

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
        _dbFilePath  = "database.sqlite";
        auto storage = getStorage(_dbFilePath);
        storage.sync_schema();
    }

    SemiFuture<Unit> DatabaseRepository::replacePlayListSongs(QVector<TPlayListSong> songs) {
        return SemiFuture<Unit>().via(dbExecutor()).thenValue([this, songs = std::move(songs)](Unit u) {
            auto storage = getStorage(_dbFilePath);
            storage.begin_transaction();
            try {
                storage.remove_all<TPlayListSong>();
//                for (const auto& song: songs) {
//                    storage.insert(song);
//                }
                storage.insert_range(songs.cbegin(),songs.cend());
                storage.commit();
            } catch (...) {
                storage.rollback();
                throw;
            }
        });
    }

    SemiFuture<QVector<TPlayListSong>> DatabaseRepository::getAllPlayListSongs() {
        return SemiFuture<Unit>().via(dbExecutor()).thenValue([this](Unit u) {
            auto storage = getStorage(_dbFilePath);
            QVector<TPlayListSong> result;
            for (auto &song: storage.iterate<TPlayListSong>(order_by(&TPlayListSong::id))) {
                result.append(song);
            }

            return result;
        });
    }
} // namespace MusicPlayer::Repository