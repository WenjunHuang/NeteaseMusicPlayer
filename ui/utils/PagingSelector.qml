import QtQuick 2.12
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.12
import "../styles/variables.mjs" as Vars
import FontAwesome 1.0

// 分页控件
Item {
    id: root
    property int total
    property int limit
    property int radius: 3
    property int columnCount: 10

    property int selectedPage: 1
    property int totalPageCount: Math.ceil(total / limit)

    signal pageChanged(int offset, int limit)

    RowLayout {
        spacing: Vars.spacing_third
        anchors.fill: parent
        Rectangle {
            radius: root.radius
            Layout.fillWidth: true
            Border {
                radius: root.radius
                commonBorderWidth: 1
                borderColor: Material.frameColor
            }
            FAIcon {
                icon: FAIcons.faAngleLeftLight
            }
        }
        Repeater {
            model: columnCount
            Rectangle {
                radius: root.radius
                Layout.fillWidth: true
                Border {
                    radius: root.radius
                    commonBorderWidth: 1
                    borderColor: Material.frameColor
                }
                Text {
                    text: index
                }
            }
        }

        Rectangle {
            radius: root.radius
            Layout.fillWidth: true
            Border {
                radius: root.radius
                commonBorderWidth: 1
                borderColor: Material.frameColor
            }
            FAIcon {
                icon: FAIcons.faAngleLeftLight
                anchors.centerIn: parent
            }
        }
    }
}
