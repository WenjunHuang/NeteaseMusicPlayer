import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import "../utils"
import "../styles/variables.mjs" as Vars
import "./personalized"

Item {
    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            spacing: 0
            Layout.fillHeight: false
            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            TabBar {
                id: tabBar
                Layout.fillWidth: false
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignHCenter
                TabButton {
                    text: "个性推荐"
                }
                TabButton {
                    text: "歌单"
                }
                TabButton {
                    text: "主播电台"
                }
                TabButton {
                    text: "排行榜"
                }
                TabButton {
                    text: "歌手"
                }
                TabButton {
                    text: "最新音乐"
                }
            }
            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: Vars.seperator_color
            Layout.topMargin: -2
            //z: -1
        }
        //        Rectangle {
        //            Layout.fillHeight: true
        //        }
        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: tabBar.currentIndex
            Personalized {
                id: banner
            }
        }
    }
}
