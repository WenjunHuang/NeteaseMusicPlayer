//
// Created by rick on 2019/11/13.
//

#pragma once
#include <QtCore/QObject>
#include "../api/data/playlist_catlist.h"

namespace MusicPlayer::Repository {
    using namespace MusicPlayer::API;

    class SongCategoryRepository : public QObject {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE(SongCategoryRepository)
        SongCategoryRepository() {}

      public:
        static void initInstance();

        static void freeInstance();

        static SongCategoryRepository* instance();

      private:
        APIPlaylistCatListData _categoryData;

        static SongCategoryRepository* _instance;
    };
} // namespace MusicPlayer::Repository
