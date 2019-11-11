//
// Created by rick on 2019/11/10.
//

#pragma once


#include <QtGui/QGuiApplication>
#include <QtQml/qqml.h>
#include "util/logger.h"
#include "api/http.h"
#include "view_models/banner_view_model.h"
#include "view_models/personalized_new_song_view_model.h"
#include "view_models/recommendation_song_lists_view_model.h"

namespace MusicPlayer {
    class Application : public QGuiApplication {
    public:
        Application(const QString &id, int& argc, char *argv[]) : QGuiApplication(argc, argv) {
          Util::Logger::initInstance();
          API::HttpWorker::initInstance();

          qmlRegisterType<ViewModels::BannerViewModel>("MusicPlayer", 1, 0, "BannerViewModel");
          qmlRegisterType<ViewModels::PersonalizedNewSongViewModel>("MusicPlayer", 1, 0,
                                                                    "PersonalizedNewSongViewModel");
          qmlRegisterType<ViewModels::RecommendationSongListsViewModel>("MusicPlayer", 1, 0,
                                                                        "RecommendationSongListsViewModel");

//          connect(this,&QGuiApplication::aboutToQuit,this,&Application::cleanup);
        }

        int exec(const QStringList &params);
    };
}



