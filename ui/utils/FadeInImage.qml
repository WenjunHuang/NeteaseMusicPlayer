import QtQuick 2.12
import QtQuick.Controls.Material 2.13

Item {
    id: root

    property Item contentItem
    signal contentLoaded()

    Rectangle {
        id: placeholder
        anchors.fill: parent
        color: Material.buttonDisabledColor

        Behavior on opacity {
            NumberAnimation {
                duration: 300
            }
        }
    }

    Item {
        id: content
        anchors.fill: parent
        opacity: 0
        Behavior on opacity {
            NumberAnimation {
                duration: 300
            }
        }
    }

    onContentLoaded: {
        placeholder.opacity = 0
        content.opacity = 1
    }

    onContentItemChanged: {
        content.data = [root.contentItem]
    }

//    Image {
//        id: image
//        source: root.source
//        anchors.fill: parent
//        opacity: 0
//        fillMode: Image.PreserveAspectFit
//        onStatusChanged: {
//            if (image.status === Image.Ready) {
//                placeholder.opacity = 0
//                image.opacity = 1
//            }
//        }

//    }
}
