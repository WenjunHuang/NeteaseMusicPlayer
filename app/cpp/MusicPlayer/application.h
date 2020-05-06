//
// Created by rick on 2019/11/10.
//

#pragma once

#include "api/data/data.h"
#include "api/http.h"
#include "util/executor.h"
#include "util/logger.h"
#include <QtGui/QGuiApplication>
#include <QtQml/qqml.h>

namespace MusicPlayer {
    class Application : public QGuiApplication {
      public:
        Application(const QString& id, int& argc, char* argv[]);

        int run(const QStringList& params);
        void initialize();
    };
} // namespace MusicPlayer
