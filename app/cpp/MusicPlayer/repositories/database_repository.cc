//
// Created by rick on 2019/12/15.
//

#include "database_repository.h"
#include "tables.h"
#include <QtCore>

namespace MusicPlayer::Repository {
    using namespace sqlite_orm;

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
        QString dbFilePath =
            QStandardPaths::locate(QStandardPaths::DataLocation, "database.sqlite", QStandardPaths::LocateFile);

        auto storage = make_storage(dbFilePath.toStdString(), TPlayListSong::table());
        _storage     = std::make_unique<decltype(storage)>(storage);
    }
} // namespace MusicPlayer::Repository