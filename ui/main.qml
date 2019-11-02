import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import MusicPlayer 1.0
import "./discover_music"
import "./styles/variables.mjs" as StyleVariables

Window {
    visible: true
    minimumWidth: 1000
    minimumHeight: 670

    Rectangle {
        anchors.fill: parent
        color: "gray"
    }

    //    BannerCarousel {
    //        id: banner
    //        anchors.left: parent.left
    //        anchors.right: parent.right
    //        height: 240
    //    }
    RecommendationSongLists {
        anchors.fill: parent
    }
}
