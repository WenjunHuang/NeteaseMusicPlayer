//
// Created by HUANG WEN JUN on 2019/12/23.
//
#include "catch2/catch.hpp"
#include "set_up.h"
#include <iostream>

#include "audio_player.h"
using namespace MusicPlayer::Player;

TEST_CASE("playSong", "[AudioPlayer]") {
    auto app        = setUp();
    auto player = AudioPlayer::instance();
    player->playAudio(347230,SongQuality::Q320000);
    app->exec();
}