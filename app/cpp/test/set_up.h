//
// Created by HUANG WEN JUN on 2019/11/29.
//
#pragma once
#include <QGuiApplication>
#include "../MusicPlayer/api/api.h"
#include "../MusicPlayer/api/data/data.h"
#include "../MusicPlayer/view_models/view_models.h"
#include "../MusicPlayer/util/executor.h"

using namespace MusicPlayer::API;
using namespace MusicPlayer::Util;

std::string testName = "test";
int argc             = 1;
char* argv[]         = {testName.data()};

QCoreApplication* setUp() {
    QGuiApplication* app = new QGuiApplication(argc, argv);
    MusicPlayer::API::registerMetaTypes();
    MusicPlayer::ViewModels::registerMetaTypes();

    AppExecutor::initInstance();
    HttpWorker::initInstance();
    MusicPlayer::Repository::SongCategoryRepository::initInstance();

    return app;
}
