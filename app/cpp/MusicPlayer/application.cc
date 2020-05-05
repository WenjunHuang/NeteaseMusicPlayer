//
// Created by rick on 2019/11/10.
//

#include "application.h"
#include "api.h"
#include "player.h"
#include "repositories.h"
#include "util.h"
#include "view_models.h"
#include <QQuickStyle>
#include <QtQml/QQmlApplicationEngine>
#include <iostream>

namespace MusicPlayer {
    int Application::run(const QStringList& params) {
        //        for (const auto& path : engine.importPathList())
        //            qDebug() << path;

        QQmlApplicationEngine engine;
        engine.addImageProvider("MusicImage",new API::ImageProvider);
        engine.addImportPath(":/ui/imports");
        engine.load("qrc:/ui/main.qml");
        return exec();
    }

    void Application::initialize() {
        // singletons
        Util::Logger::initInstance();
        Util::AppExecutor::initInstance();
        API::MusicHttpWorker::initInstance();
        Repository::DatabaseRepository::initInstance();
        Service::PlayListRepository::initInstance();
        Player::AudioPlayer::initInstance();

        // api
        API::MusicAPI::registerMetaTypes();

        // 注册Viewmodel的metatype
        ViewModels::registerMetaTypes();

        qmlRegisterUncreatableType<ViewModels::StateKinds>("MusicPlayer", 1, 0, "StateKinds", "Uncreateable");
        qmlRegisterType<ViewModels::BannerViewModel>("MusicPlayer", 1, 0, "BannerViewModel");
        qmlRegisterType<ViewModels::PersonalizedNewSongViewModel>("MusicPlayer", 1, 0, "PersonalizedNewSongViewModel");
        qmlRegisterType<ViewModels::RecommendationSongListsViewModel>("MusicPlayer", 1, 0, "RecommendationSongListsViewModel");
        qmlRegisterType<ViewModels::SongCategoryListViewModel>("MusicPlayer", 1, 0, "SongCategoryListViewModel");
        qmlRegisterType<ViewModels::SongListHighQualityBannerViewModel>(
            "MusicPlayer", 1, 0, "SongListHighQualityBannerViewModel");
        qmlRegisterType<ViewModels::SongCategoryPlayListsViewModel>("MusicPlayer", 1, 0, "SongCategoryPlayListsViewModel");
        qmlRegisterType<ViewModels::DJBannerViewModel>("MusicPlayer", 1, 0, "DJBannerViewModel");
    }

    Application::Application(const QString& id, int& argc, char** argv) : QGuiApplication(argc, argv) {
        initialize();

        //          connect(this,&QGuiApplication::aboutToQuit,this,&Application::cleanup);
    }
} // namespace MusicPlayer
