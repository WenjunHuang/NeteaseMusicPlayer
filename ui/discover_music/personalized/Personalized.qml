import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import "../../styles/variables.mjs" as Vars

Item {
    id: root
    ScrollView {
        id:scroll
        clip: true
        anchors.fill: parent
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        contentHeight: layout.height


        ColumnLayout {
            id:layout
            //minimumWidth: Vars.content_minimum_width
            //maximumWidth: Vars.content_maximum_width
            width: root.width
            spacing:Vars.spacingX3
            Rectangle {
                height: 0
                Layout.fillWidth: true
            }

            BannerCarousel {
                Layout.minimumWidth: Vars.content_minimum_width
                Layout.maximumWidth: Vars.content_maximum_width
                Layout.alignment: Qt.AlignCenter
                height: 240
            }

            RecommendationSongLists {
                Layout.minimumWidth: Vars.content_minimum_width
                Layout.maximumWidth: Vars.content_maximum_width
                Layout.alignment: Qt.AlignCenter
            }

            PersonalizedNewSongs {
                Layout.minimumWidth: Vars.content_minimum_width
                Layout.maximumWidth: Vars.content_maximum_width
                Layout.alignment: Qt.AlignCenter
            }
        }
    }
}
