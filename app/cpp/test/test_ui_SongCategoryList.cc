//
// Created by HUANG WEN JUN on 2019/11/29.
//

#include "../MusicPlayer/view_models/song_category_list_view_model.h"
#include "./catch2/catch.hpp"
#include "set_up.h"
#include <QQuickView>
#include <QtCore>
#include <QtGui/QGuiApplication>
#include <iostream>

TEST_CASE("song_category_list", "[Views]") {
    auto app = setUp();
    QQuickView view(QUrl("qrc:/ui/song_list/SongCategoryList.qml"));

    app->exec();
}