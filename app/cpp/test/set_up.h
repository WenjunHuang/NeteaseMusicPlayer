//
// Created by HUANG WEN JUN on 2019/11/29.
//
#pragma once
#include "../MusicPlayer/api/api.h"
#include "../MusicPlayer/api/data/data.h"
#include "../MusicPlayer/application.h"
#include "../MusicPlayer/util/executor.h"
#include "../MusicPlayer/view_models/view_models.h"
#include <QGuiApplication>
#include <QQuickStyle>

using namespace MusicPlayer::API;
using namespace MusicPlayer::Util;
using namespace MusicPlayer;

std::string testName = "test";
int argc             = 1;
char* argv[]         = {testName.data()};

Application* setUp() {
    QQuickStyle::addStylePath(":/ui");
    QQuickStyle::setStyle("MusicPlayer");

    Application* app = new Application("test", argc, argv);
    return app;
}
