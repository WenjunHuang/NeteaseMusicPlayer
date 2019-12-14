#include "application.h"
#include "util/misc.h"
#include <QQmlApplicationEngine>
#include <QtQuickControls2/QQuickStyle>
#include <memory>

int main(int argc, char* argv[]) {
    using namespace MusicPlayer;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    try {
//        QQuickStyle::addStylePath(":/ui");
//        QQuickStyle::setStyle("MusicPlayer");
//        QQuickStyle::setFallbackStyle("Material");
        //    QQuickStyle::setStyle("Material");
        //    QQuickStyle::setFallbackStyle("Fusion");
        std::unique_ptr<Application> application{
            std::make_unique<Application>(Util::getUserIDString(), argc, argv)};
        application->run(QStringList());
    } catch (...) {}
}