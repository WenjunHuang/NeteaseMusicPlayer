import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.13
import QtQuick.Layouts 1.13
import MusicPlayer 1.0
import FontAwesome 1.0
import "../../utils"
import "../../styles/variables.mjs" as Vars

Item {
    id: root
    implicitHeight: layout.implicitHeight
    ColumnLayout {
        id: layout
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: Vars.spacing

        PersonalizedNewSongViewModel {
            id: viewModel
        }

        RowLayout {
            spacing: Vars.spacing
            Text {
                Layout.alignment: Qt.AlignLeading | Qt.AlignVCenter
                text: "最新音乐"
                font.pixelSize: Vars.font_size_lg
                font.weight: Font.Bold
            }
            FAIcon {
                Layout.alignment: Qt.AlignLeading | Qt.AlignVCenter
                icon: FAIcons.faAngleRightLight
                size: Vars.font_size_lg
            }
        }

        GridLayout {
            id: grid
            Layout.fillHeight: false
            flow: GridLayout.TopToBottom

            columns: 2
            rows: 5
            columnSpacing: Vars.spacingX2

            Repeater {
                model: viewModel.newSongListModel
                delegate: delegate
            }
        }

        Component {
            id: delegate
            Rectangle {
                Layout.preferredHeight: 78
                Layout.fillWidth: true
                color: "transparent"
                ColumnLayout {
                    anchors.fill: parent
                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: Material.frameColor
                    }

                    RowLayout {
                        //            Layout.row: index % 5
                        //            Layout.column: Math.floor(index / 5)
                        Layout.margins: Vars.spacing
                        spacing: Vars.spacing_half

                        RoundCorner {
                            Layout.preferredWidth: 62
                            Layout.preferredHeight: 62
                            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeading
                            radius: Vars.border_radius
                            Image {
                                id: image
                                source: "image://MusicImage/"+imageUrl
                                sourceSize:Qt.size(image.width,image.height)
                                anchors.fill: parent
                                fillMode: Image.PreserveAspectFit
                                mipmap: true
                            }
                        }
                        Text {
                            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeading
                            text: ("0" + (index + 1)).slice(-2)
                            font.pixelSize: Vars.font_size
                        }
                        ColumnLayout {
                            spacing: Vars.spacing_half
                            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeading
                            RowLayout {
                                Text {
                                    wrapMode: Text.Wrap
                                    text: name
                                }
                                Text {
                                    Layout.fillWidth: true
                                    text: "(" + nameAlias + ")"
                                    visible: nameAlias ? true : false
                                }
                            }

                            Text {
                                text: artists
                            }
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: Material.frameColor
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                }
            }
        }

        Rectangle {
            Layout.fillHeight: true
        }
    }
}
