import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import MusicPlayer 1.0
import "./discover_music/personal_recommendation"
import "./styles/variables.mjs" as StyleVariables

Window {
    visible:true
    height:100
    width:200
    Rectangle{
    anchors.fill:parent
    color:StyleVariables.syntax_header_color
    }

    BannerCarousel {
    anchors.left: parent.left
    anchors.right: parent.right
        height: 240
        id:banner
    }
}