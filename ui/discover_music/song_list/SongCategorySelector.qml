import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import FontAwesome 1.0
import "../../styles/variables.mjs" as Vars
import "../../utils"

Item {
    id: root
    property string currentCategoryName: "全部"
    height: layout.implicitHeight
    RowLayout {
        id: layout
        anchors.left: parent.left
        anchors.right: parent.right
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
                console.log(Material.buttonColor)
                background.border.width = 1
                background.border.color = Material.frameColor
            }

            //            Border {
            //                target: selectorButton.background
            //                radius: selectorButton.radius
            //                commonBorderWidth: 1
            //                color: Material.frameColor
            //            }
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
                x: leftInset
                y: parent.height
                id: popup
                currentSelectedCategoryName: currentCategoryName
                onCurrentSelectedCategoryNameChanged: {
                    root.currentCategoryName = currentSelectedCategoryName
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
        }
    }
}
