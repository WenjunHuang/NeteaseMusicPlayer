//
// Created by rick on 2019/11/10.
//

#include "application.h"
#include "api.h"
#include "player.h"
#include "repository.h"
#include "util.h"
#include "view_model.h"
#include <QQuickStyle>
#include <QtQml/QQmlApplicationEngine>
#include <iostream>

namespace MusicPlayer {
    int Application::run(const QStringList& params) {
        //        for (const auto& path : engine.importPathList())
        //            qDebug() << path;

        QQmlApplicationEngine engine;
        engine.addImageProvider("MusicImage", new API::ImageProvider);
        engine.addImportPath(":/ui/imports");
        engine.load("qrc:/ui/main.qml");
        return exec();
    }

    void Application::initialize() {
        // initialize modules
        Util::initUtilModule();
        API::initAPIModule();
        Repository::initRepositoryModule();
        Service::initServiceModule();
        Player::initPlayerModule();
        ViewModel::initViewModelModule();
    }

    Application::Application(const QString& id, int& argc, char** argv) : QGuiApplication(argc, argv) {
        initialize();

        //          connect(this,&QGuiApplication::aboutToQuit,this,&Application::cleanup);
    }
} // namespace MusicPlayer
