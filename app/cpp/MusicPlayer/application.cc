//
// Created by rick on 2019/11/10.
//

#include "application.h"
#include "api/data/data.h"
#include "view_models/view_models.h"
#include <QQuickStyle>
#include <QtQml/QQmlApplicationEngine>

namespace MusicPlayer {
    int Application::exec(const QStringList& params) {
        QQmlApplicationEngine engine;
        // 注册api的metatype
        API::registerMetaTypes();

        // 注册Viewmodel的metatype
        ViewModels::registerMetaTypes();

        engine.addImportPath(":/ui");
        for (const auto& path : engine.importPathList())
            qDebug() << path;

        engine.load("qrc:/ui/main.qml");
        return QGuiApplication::exec();
    }
} // namespace MusicPlayer
