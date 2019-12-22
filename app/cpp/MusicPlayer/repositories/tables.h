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
        int id;
        SongId songId;
        std::string name;
        std::string coverImgUrl;
        int duration;
        std::string qualities;
        std::string artists; // id1:name,id2:name,...
        AlbumId albumId;
        std::string albumName;
        std::unique_ptr<MusicVideoId> musicVideoId;

        static inline auto table() {
            return make_table("songs",
                              make_column("id", &TPlayListSong::id, primary_key()),
                              make_column("songId", &TPlayListSong::songId),
                              make_column("name", &TPlayListSong::name),
                              make_column("coverImgUrl", &TPlayListSong::coverImgUrl),
                              make_column("duration", &TPlayListSong::duration),
                              make_column("qualities", &TPlayListSong::qualities),
                              make_column("albumId", &TPlayListSong::albumId),
                              make_column("albumName", &TPlayListSong::albumName),
                              make_column("artists", &TPlayListSong::artists),
                              make_column("musicVideoId", &TPlayListSong::musicVideoId));
        }
    };
} // namespace MusicPlayer::Repository
