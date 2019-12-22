//
// Created by rick on 2019/12/15.
//

#pragma once

namespace MusicPlayer {
    using SongId       = int;
    using AlbumId      = int;
    using ArtistId     = int;
    using MusicVideoId = int;

    enum class SongQuality : int { Q96000 = 9600, Q160000 = 160000, Q320000 = 320000, Q990000 = 990000 };
} // namespace MusicPlayer
