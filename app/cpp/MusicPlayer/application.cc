//
// Created by rick on 2019/11/10.
//

#include <QtQml/QQmlApplicationEngine>
#include <QQuickStyle>
#include "application.h"

namespace MusicPlayer {
    int Application::exec(const QStringList &params) {
      QQmlApplicationEngine engine;
      engine.addImportPath(":/ui");
      for (const auto &path:engine.importPathList())
        qDebug() << path;

      engine.load("qrc:/ui/main.qml");
      return QGuiApplication::exec();
    }
}
