import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtGraphicalEffects 1.13
import MusicPlayer 1.0
import FontAwesome 1.0
import "../../styles/variables.mjs" as Vars
import "../../utils"

Item {
    id: root
    implicitHeight: layout.implicitHeight
    property int itemCountPerRow: 5
    ColumnLayout {
        id: layout
        spacing: Vars.spacing
        anchors.left: parent.left
        anchors.right: parent.right

        RecommendationSongListsViewModel {
            id: viewModel
        }

        RowLayout {
            spacing: Vars.spacing
            Text {
                Layout.alignment: Qt.AlignJustify
                text: "推荐歌单"
                font.pixelSize: Vars.font_size_lg
                font.weight: Font.Bold
            }
            FAIcon {
                Layout.alignment: Qt.AlignJustify
                icon: FAIcons.faAngleRightLight
                size: Vars.font_size_lg
            }
        }

        GridLayout {
            id: grid
            Layout.fillWidth: true

            columns: itemCountPerRow
            columnSpacing: Vars.spacingX2
            rowSpacing: Vars.spacingX2

            Repeater {
                model: viewModel.songLists
                delegate: gridDelegate
            }
        }

        Component {
            id: gridDelegate
            ColumnLayout {
                spacing: 0
                Layout.preferredWidth: 1
                Layout.fillWidth: true
                Loader {
                    id: loader
                    property var modelImageUrl: imageUrl
                    property var modelPlayCount: playCount
                    property var modelName: name
                    property var modelWeekday: weekday
                    property var modelToday: today
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1
                    sourceComponent: kind == RecommendationSongListsViewModel.Normal ? normalDelegate : todayDelegate
                }
                Rectangle {
                    Layout.fillHeight: true
                }
            }
        }

        Component {
            id: normalDelegate
            FadeInImage {
                id: fadeInImage
                Layout.preferredWidth: 1
                Layout.fillWidth: true
                implicitHeight: content.implicitHeight
                contentItem: ColumnLayout {
                    id: content
                    spacing: Vars.spacing
                    anchors.left: parent.left
                    anchors.right: parent.right

                    RoundCorner {
                        // 背景图
                        Layout.fillWidth: true
                        radius: Vars.border_radius
                        implicitHeight: width
                        LinearGradientBlend {
                            target: image
                            anchors.fill: parent
                            Image {
                                id:image
                                source: modelImageUrl
                                anchors.fill: parent
                                fillMode: Image.PreserveAspectFit
                                onStatusChanged: {
                                    if (image.status === Image.Ready)
                                        fadeInImage.contentLoaded()
                                }
                                visible: false
                            }
                        }

                        FAIcon {
                            icon: FAIcons.faEyeLight
                            color: "white"
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

                        FAIcon {
                            id: playIcon
                            icon: FAIcons.faPlayCircleLight
                            size: 20
                            color: "white"
                            visible: false
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
        }

        Component {
            id: todayDelegate
            ColumnLayout {
                id: content
                spacing: Vars.spacing
                RoundCorner {
                    radius: Vars.border_radius
                    Layout.fillWidth: true
                    implicitHeight: width
                    Image {
                        id: image
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        source: modelImageUrl
                        visible: false
                    }
                    FastBlur {
                        anchors.fill: image
                        source: image
                        radius: 64
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
}
