//
// Created by rick on 2019/12/19.
//
#include "catch2/catch.hpp"
#include "set_up.h"
#include <iostream>

#include "../MusicPlayer/repositories/database_repository.h"
#include "../MusicPlayer/services/play_list_repository.h"
using namespace MusicPlayer::Repository;
using namespace MusicPlayer::Service;

TEST_CASE("insertSongs", "[Repository]") {
    auto app        = setUp();
    auto repository = DatabaseRepository::instance();
    //    SongId id;
    //    QString name;
    //    QString coverImgUrl;
    //    int duration;
    //    QString qualities;
    //    QString artistsNames;
    std::vector<TPlayListSong> data;
    repository->replacePlayListSongs(std::move(data)).via(mainExecutor()).thenTry([](folly::Try<Unit> value) {
        if (value.hasException())
            qDebug() << "has exception " << value.exception().get_exception()->what();
        qApp->quit();
    });
    app->exec();
}

TEST_CASE("getAllSongs", "[Repository]") {
    auto app        = setUp();
    auto repository = DatabaseRepository::instance();

    repository->getAllPlayListSongs().via(mainExecutor()).thenValue([](std::vector<TPlayListSong>&& songs) {
        for (const auto& song : songs) {
            std::cout << song.songId << std::endl;
        }
    });
}

TEST_CASE("addSongs", "[Repository]") {
    auto app        = setUp();
    auto repository = PlayListRepository::instance();

    QVector<PlayListSong> songs;
    for (auto i = 0; i < 9182; i++) {
        songs.append(PlayListSong{
            i,
            QString::fromUtf8(u8"真的汉字"),
            "http://example",
            PlayListSongAlbum{1, QString::fromUtf8(u8"牛逼")},
            121,
            {SongQuality::Q990000, SongQuality::Q96000, SongQuality::Q160000},
            {
                PlayListSongArtist{
                    1, QString::fromUtf8(u8"牛逼天王😈🎁📝📁💼🖍🖋😁😁🤦‍♀️🤷‍♂️😊")},
            },
            std::nullopt,
        });
    }

    repository->loadFromDb();

    repository->allSongsInPlayList();

}

TEST_CASE("loadFromDb", "[Repository]") {
    auto app        = setUp();
    auto repository = PlayListRepository::instance();

    repository->loadFromDb();
    auto songs = repository->allSongsInPlayList();
    std::for_each(songs.cbegin(),songs.cend(),[](const auto& song) {
        std::cout << song.id << std::endl;
        qDebug() << song.name;
    });

}
