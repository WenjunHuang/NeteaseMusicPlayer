//
// Created by rick on 2019/12/19.
//
#include "catch2/catch.hpp"
#include "set_up.h"
#include <iostream>

#include "../MusicPlayer/repositories/database_repository.h"
using namespace MusicPlayer::Repository;

TEST_CASE("insertSongs", "[Repository]") {
    auto app        = setUp();
    auto repository = DatabaseRepository::instance();
    //    SongId id;
    //    QString name;
    //    QString coverImgUrl;
    //    int duration;
    //    QString qualities;
    //    QString artistsNames;
    QVector<TPlayListSong> data{
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
        {1, "Ok", "http://empty", 60, "3200,6000,99000", "foo/bar"},
    };
    repository->replacePlayListSongs(data).via(mainExecutor()).thenTry([](folly::Try<Unit> value) {
        if (value.hasException())
            qDebug() << "has exception " << value.exception().get_exception()->what();
        qApp->quit();
    });
    app->exec();
}

TEST_CASE("getAllSongs", "[Repository]") {
    auto app        = setUp();
    auto repository = DatabaseRepository::instance();

    repository->getAllPlayListSongs().via(mainExecutor()).thenValue([](QVector<TPlayListSong> songs){
        for (const auto& song: songs) {
            std::cout << song.id << std::endl;
        }

    });
}