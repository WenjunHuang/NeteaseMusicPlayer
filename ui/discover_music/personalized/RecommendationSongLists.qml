import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtGraphicalEffects 1.13
import MusicPlayer 1.0
import "../../styles/variables.mjs" as Vars
import "../../octicons"
import "../../utils"

ColumnLayout {
    id: root
    spacing: Vars.spacing
    property int itemCountPerRow: 5

    RecommendationSongListsViewModel {
        id: viewModel
    }

    Text {
        text: "推荐歌单 >"
        font.pixelSize: Vars.font_size_lg
        font.weight: Font.Bold
        Layout.fillWidth: true
    }

    GridLayout {
        id: grid
        //Layout.fillHeight: false
        anchors.left: parent.left
        anchors.right: parent.right

        columns: itemCountPerRow
        columnSpacing: Vars.spacingX2
        rowSpacing: Vars.spacingX2

        Repeater {
            model: viewModel.songLists
            delegate: delegate
        }
    }

    //    Rectangle {
    //        Layout.fillHeight: true
    //    }
    Component {
        id: delegate
        ColumnLayout {
            spacing: 0
            Loader {
                id: loader
                property var modelImageUrl: imageUrl
                property var modelPlayCount: playCount
                property var modelName: name
                property var modelWeekday: weekday
                property var modelToday: today
                Layout.preferredWidth: (grid.width - (itemCountPerRow - 1)
                                        * grid.columnSpacing) / itemCountPerRow
                sourceComponent: kind == RecommendationSongListsViewModel.Normal ? normalDelegate : todayDelegate
            }
            Rectangle {
                Layout.fillHeight: true
            }
        }
    }

    Component {
        id: normalDelegate
        ColumnLayout {
            id: content
            spacing: Vars.spacing

            RoundCorner {
                radius: Vars.border_radius
                // 背景图
                Layout.preferredWidth: (grid.width - (itemCountPerRow - 1)
                                        * grid.columnSpacing) / itemCountPerRow
                Layout.preferredHeight: Layout.preferredWidth

                Image {
                    id: image
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: modelImageUrl
                    visible: false
                }

                LinearGradient {
                    id: gradient
                    anchors.fill: parent
                    start: Qt.point(0, 0)
                    end: Qt.point(0, 300)
                    gradient: Gradient {
                        GradientStop {
                            position: 0.0
                            color: Vars.box_selected_border_color
                        }
                        GradientStop {
                            position: 0.3
                            color: "white"
                        }
                    }
                    visible: false
                }

                Blend {
                    // 加入一点颜色混合，使得"播放数"文字能比较突出
                    anchors.fill: image
                    source: image
                    foregroundSource: gradient
                    mode: "darken"
                }

                Octicon {
                    symbol: "eye"
                    width: 16
                    height: 16
                    color: "white"
                    showColor: true
                    anchors.right: textPlayCount.left
                    anchors.rightMargin: Vars.spacing_third
                    anchors.verticalCenter: textPlayCount.verticalCenter
                }

                Text {
                    // 播放数
                    id: textPlayCount
                    font.pixelSize: Vars.font_size
                    color: "white"
                    text: modelPlayCount
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.rightMargin: Vars.spacing_half
                    anchors.topMargin: Vars.spacing_half
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        playIcon.visible = true
                    }
                    onExited: {
                        playIcon.visible = false
                    }
                }

                Octicon {
                    id: playIcon
                    visible: false
                    symbol: "play"
                    width: 20
                    height: 22
                    color: "white"
                    showColor: true
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.rightMargin: Vars.spacing
                    anchors.bottomMargin: Vars.spacing
                }
            }
            Text {
                id: nameText
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
                text: modelName
                font.pixelSize: Vars.font_size_md
            }
        }
    }

    Component {
        id: todayDelegate
        ColumnLayout {
            RoundCorner {
                radius: Vars.border_radius
                Layout.preferredWidth: (grid.width - (itemCountPerRow - 1)
                                        * grid.columnSpacing) / itemCountPerRow
                Layout.preferredHeight: Layout.preferredWidth
                Image {
                    id: image
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: modelImageUrl
                    visible: false
                }
                GaussianBlur {
                    anchors.fill: image
                    source: image
                    radius: 10
                    samples: 20
                }
                Text {
                    text: modelWeekday
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: Vars.spacing_half
                }
                Text {
                    text: modelToday
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }
            Text {
                id: nameText
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
                text: modelName
                font.pixelSize: Vars.font_size_md
            }
//            Rectangle {
//                Layout.fillHeight: true
//            }
        }
    }
}
