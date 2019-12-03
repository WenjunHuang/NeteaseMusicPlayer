import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import "../../styles/variables.mjs" as Vars

Item {
    id: root

    ScrollView {
        id: scroll
        clip: true
        anchors.fill: parent
        //ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        contentHeight: layout.height
        contentWidth: width

        RowLayout {
            id: layout
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: 0
            Rectangle {
                Layout.minimumWidth: Vars.spacingX2
                Layout.fillWidth: true
            }

            ColumnLayout {
                Layout.minimumWidth: Vars.content_minimum_width
                Layout.maximumWidth: Vars.content_maximum_width
                Layout.fillWidth: true
                spacing: Vars.spacingX3
                Rectangle {
                    height: 0
                    color:"transparent"
                    Layout.fillWidth: true
                }

                BannerCarousel {
                    Layout.fillWidth: true
                    Layout.fillHeight: false
                    Layout.alignment: Qt.AlignCenter
                    height: 240
                }

                RecommendationSongLists {
                    Layout.fillWidth: true
                    Layout.fillHeight: false
                    Layout.alignment: Qt.AlignCenter
                }

                PersonalizedNewSongs {
                    Layout.fillWidth: true
                    Layout.fillHeight: false
                    Layout.alignment: Qt.AlignCenter
                }
            }
            Rectangle {
                Layout.minimumWidth: 20
                Layout.fillWidth: true
            }
        }
    }
}
