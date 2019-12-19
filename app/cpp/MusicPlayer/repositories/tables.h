//
// Created by rick on 2019/12/15.
//

#pragma once
#include "../commons.h"
#include "../util/sqlite_orm.h"
#include <QtCore>
#include <string>

namespace MusicPlayer::Repository {
    using namespace sqlite_orm;
    struct TPlayListSong {
        SongId id;
        std::string name;
        std::string coverImgUrl;
        int duration;
        std::string qualities;
        std::string artistsNames;

        static inline auto table() {
            return make_table("songs",
                              make_column("id", &TPlayListSong::id, primary_key()),
                              make_column("name", &TPlayListSong::name),
                              make_column("coverImgUrl", &TPlayListSong::coverImgUrl),
                              make_column("duration", &TPlayListSong::duration),
                              make_column("qualities", &TPlayListSong::qualities),
                              make_column("artistsNames", &TPlayListSong::artistsNames));
        }
    };
} // namespace MusicPlayer::Repository
