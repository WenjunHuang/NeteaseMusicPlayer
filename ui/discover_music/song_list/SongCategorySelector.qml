import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.13
import FontAwesome 1.0
import "../../styles/variables.mjs" as Vars

RowLayout {
    spacing: 0
    property string currentCategoryName: "全部"
    RoundButton {
        id: selectorButton
        Layout.fillWidth: false
        radius: height / 2
        leftPadding: height
        rightPadding: height
        text: currentCategoryName
        Material.elevation: 1

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

        Behavior on width {
            NumberAnimation {
                duration: 200
            }
        }

        Popup {
            x: leftInset
            y: parent.height
            id: popup
            SongCategoryMenu {}
        }
    }

    Rectangle {
        Layout.fillWidth: true
    }
}
