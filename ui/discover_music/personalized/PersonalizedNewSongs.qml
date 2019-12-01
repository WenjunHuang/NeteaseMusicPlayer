import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.13
import QtQuick.Layouts 1.13
import MusicPlayer 1.0
import "../../utils"
import "../../styles/variables.mjs" as Vars

ColumnLayout {
    id: root
    spacing: Vars.spacing

    PersonalizedNewSongViewModel {
        id: viewModel
    }

    Text {
        text: "最新音乐 >"
        font.pixelSize: Vars.font_size_lg
        font.weight: Font.Bold
        Layout.fillWidth: true
    }

    GridLayout {
        id: grid
        Layout.fillHeight: false
        //Layout.fillWidth: true
        //anchors.left: parent.left
        //anchors.right: parent.right

        columns: 2
        columnSpacing: Vars.spacingX2

        Repeater {
            model: viewModel.newSongListModel
            delegate: delegate
        }
    }

    Component {
        id: delegate
        RowLayout {
            Layout.preferredHeight: 78
            Layout.row: index % 5
            Layout.column: Math.floor(index / 5)
            Layout.margins: Vars.spacing
            spacing: Vars.spacing_half

            Component.onCompleted: {
                console.log(`${index % 5},${Math.floor(index / 5)}`)
            }

            RoundCorner {
                Layout.preferredWidth: 62
                Layout.preferredHeight: 62
                radius: Vars.border_radius
                Image {
                    source: imageUrl
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    mipmap: true
                }
            }
            Text {
                text: ("0" + (index + 1)).slice(-2);
                font.pixelSize: Vars.font_size
            }
            ColumnLayout {
                spacing: Vars.spacing_half
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

                Text{
                    text:artists
                }
            }
        }
    }

    Rectangle {
        Layout.fillHeight: true
    }
}
