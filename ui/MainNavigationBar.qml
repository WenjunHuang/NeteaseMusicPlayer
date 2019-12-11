import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import "./styles/variables.mjs" as Vars
import FontAwesome 1.0

Item {
    readonly property var iconMaps: {
        "发现音乐": FAIcons.faMusicLight,
        "私人FM": FAIcons.faBroadcastTowerLight,
        "视频": FAIcons.faVideoLight,
        "朋友": FAIcons.faUserFriendsLight
    }

    ListModel {
        id: mainNavModel
        ListElement {
            name: "发现音乐"
        }
        ListElement {
            name: "私人FM"
        }
        ListElement {
            name: "视频"
        }
        ListElement {
            name: "朋友"
        }
    }

    Component {
        id: mainNavViewDelegate
        Item {
            id: wrapper
            height: layout.height
            width: wrapper.ListView.view.width
            RowLayout {
                id: layout
                spacing: Vars.spacing_half
                height: 35
                width: wrapper.ListView.view.width
                Rectangle {
                    Layout.preferredWidth: Vars.spacing
                    Layout.fillHeight: true
                    Layout.fillWidth: false
                    color: "transparent"
                }
                FAIcon {
                    icon: iconMaps[model.name]
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: false
                    size: Vars.font_size_md
                    color: wrapper.ListView.isCurrentItem ? Material.accentColor : Material.primaryTextColor
                }
                Text {
                    text: model.name
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: false
                    font.pixelSize: Vars.font_size_md
                    color: wrapper.ListView.isCurrentItem ? Material.accentColor : Material.primaryTextColor
                }
                Rectangle {
                    Layout.fillWidth: true
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    listView.currentIndex = index
                }
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        ToolBar {
            Layout.fillHeight: false
            //Layout.preferredHeight: 50
            Layout.fillWidth: true
            Material.background: Material.backgroundColor
            Material.elevation: 0
            spacing: 0
            RowLayout {
                spacing: 0
                anchors.fill: parent

                Rectangle {
                    Layout.fillWidth: true
                    color: "transparent"
                }

                ToolButton {
                    Layout.fillWidth: false
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    text: FAIcons.faAngleLeftLight.code
                    font.family: FAIcons.faAngleLeftLight.family
                    font.pixelSize: Vars.font_size_xl
                    enabled: mainStackView.depth > 1
                    onClicked: {
                        mainStackView.pop()
                    }
                }

                ToolButton {
                    Layout.fillWidth: false
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    text: FAIcons.faAngleRightLight.code
                    font.family: FAIcons.faAngleRightLight.family
                    font.pixelSize: Vars.font_size_xl
                }
            }
        }

        ListView {
            id: listView
            model: mainNavModel
            Layout.fillWidth: true
            Layout.fillHeight: true
            highlight: Rectangle {
                color: Material.primaryHighlightedTextColor
            }
            snapMode: ListView.SnapToItem
            focus: true
            keyNavigationEnabled: false

            delegate: mainNavViewDelegate
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
