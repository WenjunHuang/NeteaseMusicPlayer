import QtQuick 2.12
import QtQuick.Controls.Material 2.13

Item {
    id: root
    property url source

    Rectangle {
        id: placeholder
        anchors.fill: parent
        color: Material.buttonDisabledColor

        Behavior on opacity {
            NumberAnimation {
                duration: 2000
            }
        }
    }

    Image {
        id: image
        source: root.source
        anchors.fill: parent
        opacity: 0
        fillMode: Image.PreserveAspectFit
        onStatusChanged: {
            if (image.status === Image.Ready) {
                placeholder.opacity = 0
                image.opacity = 1
            }
        }

        Behavior on opacity {
            NumberAnimation {
                duration: 2000
            }
        }
    }
}
