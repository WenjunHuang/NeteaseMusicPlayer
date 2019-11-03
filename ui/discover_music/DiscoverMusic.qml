import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

Pane {
    ColumnLayout {
        width: parent.width
        RowLayout {
            Item{
                Layout.fillWidth: true
            }

            TabBar {
                id: tabBar
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignHCenter
                height: 100
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
            Item{
                Layout.fillWidth: true
            }
        }
        Rectangle {
            Layout.fillWidth: true
            height:1
            color:"black"
            //Layout.topMargin: -10
            z:-1
        }

        Rectangle{
            Layout.fillHeight: true
        }

        //        StackLayout{
        //            Layout.fillWidth: true
        //            currentIndex: tabBar.currentIndex
        //            Pane{
        //            }
        //        }
    }
}
