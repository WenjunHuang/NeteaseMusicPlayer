//
// Created by HUANG WEN JUN on 2019/12/9.
//

#pragma once
#include <QtCore>

namespace MusicPlayer::Repository {
    using SongId = int;
    using AlbumId = int;
    using ArtistId = int;

    enum class SongQuality {
        Q96000,
        Q160000,
        Q320000,
    };

    struct Song {
        SongId id;
        QString name;
        ArtistId artistId;
        AlbumId albumId;
    };
}
