import QtQuick 2.12
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.12
import "../styles/variables.mjs" as Vars
import FontAwesome 1.0
import "PagingSelector.js" as Code

// 分页控件
Item {
    id: root

    property int total

    property int limit
    property int offset

    property int pageItemRadius: 3
    property int pageItemSize: 24

    property int columnCount: 10

    property int selectedPage: Math.floor(offset / limit) + 1
    property int totalPageCount: Math.ceil(total / limit)

    implicitWidth: layout.implicitWidth
    implicitHeight: layout.implicitHeight
    RowLayout {
        id: layout
        spacing: Vars.spacing_third
        Rectangle {
            radius: pageItemRadius
            Layout.preferredWidth: pageItemSize
            Layout.preferredHeight: pageItemSize
            Border {
                radius: pageItemRadius
                commonBorderWidth: 1
                borderColor: Material.frameColor
            }
            FAIcon {
                icon: FAIcons.faAngleLeftLight
                anchors.centerIn: parent
            }
            MouseArea {
                visible: selectedPage !== 1
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    root.offset = (selectedPage - 2) * limit
                }
            }
        }
        Repeater {
            model: Code.createPageModel()
            Rectangle {
                radius: pageItemRadius
                Layout.preferredWidth: pageItemSize
                Layout.preferredHeight: pageItemSize
                color: modelData.selected ? Material.accentColor : Material.backgroundColor

                Border {
                    radius: pageItemRadius
                    commonBorderWidth: 1
                    borderColor: Material.frameColor
                }
                Text {
                    anchors.centerIn: parent
                    text: modelData.text
                    color:
                        modelData.click ? (modelData.selected ? Material.primaryHighlightedTextColor : Material.primaryTextColor): Material.color(Material.Grey,Material.Shade100)
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    visible: modelData.click !== undefined ? true : false
                    onClicked: {
                        modelData.click()
                    }
                }
            }
        }

        Rectangle {
            radius: pageItemRadius
            Layout.preferredWidth: pageItemSize
            Layout.preferredHeight: pageItemSize
            Border {
                radius: pageItemRadius
                commonBorderWidth: 1
                borderColor: Material.frameColor
            }
            FAIcon {
                icon: FAIcons.faAngleRightLight
                anchors.centerIn: parent
            }
        }
    }
}
