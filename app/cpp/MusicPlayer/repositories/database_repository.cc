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

    SemiFuture<Unit> DatabaseRepository::replacePlayListSongs(std::vector<TPlayListSong>&& songs) {
        return SemiFuture<Unit>().via(dbExecutor()).thenValue([this, songs = std::move(songs)](Unit u) {
            int batchSize = 10;
            auto storage  = getStorage(_dbFilePath);
            storage.begin_transaction();
            try {
                storage.remove_all<TPlayListSong>();
                //                for (const auto& song: songs) {
                //                    storage.insert(song);
                //                }
                auto start = songs.cbegin();
                int count = 0;
                for (auto index = songs.cbegin();index < songs.cend();index++) {
                    if (count != 0 && (count  % batchSize) == 0) {
                        storage.insert_range(start, index);
                        start = index;
                    }
                    count++;
                }
                if (start < songs.cend())
                    storage.insert_range(start, songs.cend());
                storage.commit();
                std::cout << "committed" << std::endl;
            } catch (...) {
                storage.rollback();
                std::cout << "rollback" << std::endl;
                throw;
            }
        });
    }

    SemiFuture<std::vector<TPlayListSong>> DatabaseRepository::getAllPlayListSongs() {
        return SemiFuture<Unit>().via(dbExecutor()).thenValue([this](Unit u) {
            auto storage = getStorage(_dbFilePath);
            return storage.get_all<TPlayListSong>(order_by(&TPlayListSong::songId));
            //            std::vector<TPlayListSong> result;
            //            for (auto &song: storage.iterate<TPlayListSong>(order_by(&TPlayListSong::songId))) {
            //                result.push_back(song);
            //            }
            //
            //            return result;
        });
    }
} // namespace MusicPlayer::Repository