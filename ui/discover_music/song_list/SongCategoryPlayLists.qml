import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import MusicPlayer 1.0
import FontAwesome 1.0
import "../../styles/variables.mjs" as Vars
import "../../utils"

Item {
    id: root
    implicitHeight: layout.implicitHeight

    property string currentCategoryName

    property var total
    property int offset: 0
    property int limit: 100

    function reload() {
        viewModel.load(root.currentCategoryName, root.limit, root.offset)
    }

    onCurrentCategoryNameChanged: {
        root.offset = 0
        root.total = null
        reload()
    }

    SongCategoryPlayListsViewModel {
        id: viewModel
        onStateChanged: {
            if (viewModel.state.kind === StateKinds.Loading) {
                layout.currentIndex = 0
            } else if (viewModel.state.kind === StateKinds.Ready) {
                if (!root.total) {
                    console.log(viewModel.state.data.total)
                    root.total = viewModel.state.data.total
                }
                console.log(viewModel.state.data.playlist)
                layout.currentIndex = 1
            }
        }
    }

    StackLayout {
        id: layout
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        implicitHeight: children[currentIndex].implicitHeight
        Loading {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
        }
        ColumnLayout {
            Layout.fillWidth: true
            GridLayout {
                columns: 5
                columnSpacing: Vars.spacing
                rowSpacing: Vars.spacingX2
                Repeater {
                    model: viewModel.state.kind
                           === StateKinds.Ready ? viewModel.state.data.playlist : null
                    ColumnLayout {
                        id: content
                        spacing: Vars.spacing
                        Layout.preferredWidth: 1
                        Layout.fillWidth: true

                        RoundCorner {
                            // 背景图
                            Layout.fillWidth: true
                            radius: Vars.border_radius
                            implicitHeight: width
                            LinearGradientBlend {
                                target: image
                                anchors.fill: parent
                                Image {
                                    source: modelData.coverImgUrl
                                    fillMode: Image.PreserveAspectFit
                                    anchors.fill: parent
                                }
                                FadeInImage {
                                    id: image
                                    anchors.fill: parent
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
                                text: modelData.playCount
                                anchors.right: parent.right
                                anchors.top: parent.top
                                anchors.rightMargin: Vars.spacing_half
                                anchors.topMargin: Vars.spacing_half
                            }

                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                onEntered: {
                                    playIcon.opacity = 0.8
                                }
                                onExited: {
                                    playIcon.opacity = 0
                                }
                            }

                            Rectangle {
                                id: playIcon
                                height: 40
                                width: 40
                                opacity: 0
                                radius: height / 2
                                color: "white"
                                anchors.right: parent.right
                                anchors.bottom: parent.bottom
                                anchors.rightMargin: Vars.spacing_half
                                anchors.bottomMargin: Vars.spacing_half

                                FAIcon {
                                    anchors.centerIn: parent
                                    icon: FAIcons.faPlaySolid
                                    size: 12
                                    color: Material.color(Material.accentColor,
                                                          Material.Shade400)
                                }

                                Behavior on opacity {
                                    NumberAnimation {
                                        duration: 200
                                    }
                                }
                            }

                            RowLayout {
                                anchors.left: parent.left
                                anchors.bottom: parent.bottom
                                anchors.leftMargin: Vars.spacing_half
                                anchors.bottomMargin: Vars.spacing_half
                                spacing: Vars.spacing_third

                                FAIcon {
                                    icon: FAIcons.faUserLight
                                    size: Vars.font_size
                                }
                                Text {
                                    text: modelData.creatorName
                                    font.pixelSize: Vars.font_size
                                    color: "white"
                                }
                            }
                        }
                        Text {
                            id: nameText
                            Layout.fillWidth: true
                            wrapMode: Text.WordWrap
                            text: modelData.name
                            font.pixelSize: Vars.font_size_md
                        }
                        Rectangle {
                            Layout.fillHeight: true
                        }
                    }
                }
            }
            PagingSelector {
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignHCenter
                total: root.total
                limit: root.limit
                offset: root.offset
                onOffsetChanged: {
                    root.offset = offset
                    reload()
                }
            }
        }
    }
}
