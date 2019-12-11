import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import "../utils"
import "../styles/variables.mjs" as Vars
import "./personalized"
import "./song_list"
import "./dj_radios"

Item {
    id: root
    property int currentIndex

    property var indexSubNavMap: {
        0:"个性推荐",
        1:"歌单",
        2:"主播电台",
        3:"排行榜",
        4:"歌手",
        5:"最新音乐"
    }
    StackView.onActivating:{
        tabBar.currentIndex = root.currentIndex
    }

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
                currentIndex: root.currentIndex
                onCurrentIndexChanged: {
                    if (currentIndex !== root.currentIndex)
                        mainStackView.push("qrc:/ui/discover_music/DiscoverMusic.qml",{"currentIndex":currentIndex})
                }

                TabButton {
                    width: implicitWidth
                    text: indexSubNavMap[0]
                }
                TabButton {
                    width: implicitWidth
                    text: indexSubNavMap[1]
                }
                TabButton {
                    width: implicitWidth
                    text: indexSubNavMap[2]
                }
                TabButton {
                    text: indexSubNavMap[3]
                    width: implicitWidth
                }
                TabButton {
                    width: implicitWidth
                    text: indexSubNavMap[4]
                }
                TabButton {
                    width: implicitWidth
                    text: indexSubNavMap[5]
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
        Loader {
            id: loader
            Layout.fillWidth: true
            Layout.fillHeight: true
            sourceComponent: {
                const index = root.currentIndex
                if (index === 0)
                    return personalized
                if (index === 1)
                    return songList
                if (index === 2)
                    return djRadios

                return foo
            }
        }
    }

    Component {
        id: personalized
        Personalized {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Component {
        id: songList
        SongList {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Component {
        id: djRadios
        DJRadios {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Component {
        id:foo
        Rectangle{}
    }
}
