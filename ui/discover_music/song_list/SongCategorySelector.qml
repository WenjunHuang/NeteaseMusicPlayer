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
    implicitHeight: loader.implicitHeight
    property string currentCategoryName: "全部"
    height: layout.implicitHeight
    visible: false
    SongCategoryListViewModel {
        id: viewModel
        onStateChanged: {
            if (state.kind === StateKinds.Ready) {
                // show ready
                console.log(state.data.hotCategories)
                loader.sourceComponent = delegate
                root.visible = true
            } else {
                root.visible = false
                loader.sourceComponent = null
            }
        }
    }
    Loader {
        id: loader
        anchors.left: parent.left
        anchors.right: parent.right
    }
    Component {
        id: delegate

        RowLayout {
            id: layout
            spacing: 0
            RoundButton {
                id: selectorButton
                Layout.fillWidth: false
                radius: height / 2
                leftPadding: height
                rightPadding: height
                text: currentCategoryName
                Material.elevation: 0
                Component.onCompleted: {
                    background.border.width = 1
                    background.border.color = Material.frameColor
                }

                FAIcon {
                    icon: FAIcons.faAngleRightLight
                    font.pixelSize: parent.font.pixelSize
                    anchors.left: parent.contentItem.right
                    anchors.leftMargin: Vars.spacing_third
                    anchors.verticalCenter: parent.verticalCenter
                }

                onClicked: {
                    popup.open()
                }

                Behavior on implicitWidth {
                    NumberAnimation {
                        duration: 200
                    }
                }

                SongCategoryMenu {
                    id: popup
                    x: leftInset
                    y: parent.height
                    modelData: viewModel.state.data
                    currentSelectedCategoryName: currentCategoryName
                    onCurrentSelectedCategoryNameChanged: {
                        root.currentCategoryName = currentSelectedCategoryName
                    }
                }
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight
                spacing: Vars.spacing_half
                Repeater {
                    model: viewModel.state.data.hotCategories.slice(0, 10)
                    Container {
                        id: control
                        horizontalPadding: Vars.spacing_third + height / 2
                        verticalPadding: Vars.spacing_third
                        hoverEnabled: true
                        contentItem: Text {
                            id: text
                            text: modelData
                            color: modelData === root.currentCategoryName ? Material.accentColor : Material.primaryTextColor
                            anchors.centerIn: parent
                            font.pixelSize: Vars.font_size_sm
                            font.bold: modelData === root.currentCategoryName ? true : (control.hovered ? true : false)
                        }
                        background: Rectangle {
                            radius: control.height / 2
                            color: modelData === root.currentCategoryName ? Material.color(Material.accentColor, Material.Shade50) : "transparent"
                        }

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: {
                                root.currentCategoryName = modelData
                            }
                        }
                    }
                }
            }
        }
    }
}
