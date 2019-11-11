#include <memory>
#include "application.h"
#include <QQmlApplicationEngine>
#include <QtQuickControls2/QQuickStyle>
#include "util/misc.h"

int main(int argc, char *argv[]) {
  using namespace MusicPlayer;
  for (int i = 0;i < argc;i++){
    qDebug() << strlen(argv[i]);
  }
  try {
    QQuickStyle::addStylePath(":/ui");
    QQuickStyle::setStyle("MusicPlayer");
//    QQuickStyle::setStyle("Material");
//    QQuickStyle::setFallbackStyle("Fusion");
//    std::unique_ptr<Application> application{std::make_unique<Application>(Util::getUserIDString(), argc, argv)};
//    auto application = new Application(Util::getUserIDString(),argc,argv);
//    application->exec(QStringList());
    Application app(Util::getUserIDString(), argc, argv);
    app.exec(QStringList());
  } catch (...) {
  }

}