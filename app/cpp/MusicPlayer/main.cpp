#include "application.h"
#include "util/misc.h"
#include <QQmlApplicationEngine>
#include <QtQuickControls2/QQuickStyle>
#include <memory>

int main(int argc, char* argv[]) {
    using namespace MusicPlayer;

    try {
        QQuickStyle::addStylePath(":/ui");
        QQuickStyle::setStyle("MusicPlayer");
        //    QQuickStyle::setStyle("Material");
        //    QQuickStyle::setFallbackStyle("Fusion");
        std::unique_ptr<Application> application{
            std::make_unique<Application>(Util::getUserIDString(), argc, argv)};
        application->exec(QStringList());
    } catch (...) {}
}