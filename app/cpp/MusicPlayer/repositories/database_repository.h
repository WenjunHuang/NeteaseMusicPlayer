//
// Created by rick on 2019/12/15.
//

#pragma once

#include "../util/sqlite_orm.h"
#include <QtCore>
#include <memory>

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

      private:
        static DatabaseRepository* _instance;
        std::unique_ptr<internal::storage_base> _storage;
    };
} // namespace MusicPlayer::Repository
