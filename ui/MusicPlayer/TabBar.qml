import QtQuick 2.13
import QtQuick.Templates 2.13 as T

T.TabBar {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)

    spacing: -1

    contentItem: ListView {
        model: control.contentModel
        currentIndex: control.currentIndex

        spacing: control.spacing
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickIfNeeded
        snapMode: ListView.SnapToItem

        highlightMoveDuration: 1000
        highlightRangeMode: ListView.ApplyRange
        preferredHighlightBegin: 40
        preferredHighlightEnd: width - 40
        highlight: Rectangle {
            z: 100
            color:"transparent"

            Rectangle {
                color: "blue"
                height: 10
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
            }
        }
    }

    background: Item {
        implicitHeight: 21

        Rectangle {
            width: parent.width
            height: 1
            y: control.position === T.TabBar.Header ? parent.height - 1 : 0
            //color: Fusion.outline(control.palette)
        }
    }
    Component.onCompleted: {
        console.log("ok")
    }
}
