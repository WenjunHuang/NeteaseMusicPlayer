import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import MusicPlayer 1.0
import "./discover_music"
import "./styles/variables.mjs" as StyleVariables

Window {
    visible: true
    minimumWidth: 1000
    minimumHeight: 670
    Flickable {
        anchors.fill: parent
        contentWidth: content.width
        contentHeight: content.height
        ColumnLayout {
            id: content

            BannerCarousel {
                id: banner
                Layout.fillWidth: true
                height: 240
            }
            RecommendationSongLists {
                Layout.fillWidth: true
            }

            PersonalizedNewSongs {
                Layout.fillWidth: true
            }
        }
    }
}
