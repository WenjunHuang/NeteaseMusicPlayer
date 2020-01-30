//
// Created by HUANG WEN JUN on 2019/11/29.
//
#pragma once
#include "../MusicPlayer/api/data/data.h"
#include "../MusicPlayer/api/music_api.h"
#include "../MusicPlayer/application.h"
#include "../MusicPlayer/util/executor.h"
#include "../MusicPlayer/view_models/view_models.h"
#include <QGuiApplication>
#include <QQuickStyle>
#include <QDebug>

using namespace MusicPlayer::API;
using namespace MusicPlayer::Util;
using namespace MusicPlayer;

std::string testName = "test";
int argc             = 1;
char* argv[]         = {testName.data()};

void messageOutput(QtMsgType type,QMessageLogContext const& context,QString const& msg) {
    QTextStream cout(stdout,QIODevice::WriteOnly);
    cout << msg << endl;
}
Application* setUp() {
    QQuickStyle::addStylePath(":/ui");
    QQuickStyle::setStyle("MusicPlayer");
    qInstallMessageHandler(messageOutput);

    Application* app = new Application("test", argc, argv);
    return app;
}
