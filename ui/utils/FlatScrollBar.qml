import QtQuick 2.12
import QtQuick.Templates 2.12 as T
import QtQuick.Controls.Material 2.12

T.ScrollBar {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    x: parent.mirrored ? 0 : parent.width - width
    y: parent.topPadding
    height: parent.availableHeight
    active: parent.ScrollBar.horizontal.active
    padding: control.interactive ? 1 : 2
    visible: control.policy !== T.ScrollBar.AlwaysOff

    contentItem: Rectangle {
        implicitWidth: control.interactive ? 6 : 2
        implicitHeight: control.interactive ? 6 : 2
        radius: Math.min(width, height) / 2

        color: control.pressed ? control.Material.scrollBarPressedColor : control.interactive
                                 && control.hovered ? control.Material.scrollBarHoveredColor : control.Material.scrollBarColor
        opacity: 0.0
    }

    //    background: Rectangle {
    //        implicitWidth: control.interactive ? 16 : 4
    //        implicitHeight: control.interactive ? 16 : 4
    //        radius: Math.min(width,height) / 2
    //        color: "#0e000000"
    //        opacity: 0.0
    //        visible: control.interactive
    //    }
    states: State {
        name: "active"
        when: control.policy === T.ScrollBar.AlwaysOn || (control.active
                                                          && control.size < 1.0)
    }

    transitions: [
        Transition {
            to: "active"
            NumberAnimation {
                targets: [contentItem]
                property: "opacity"
                to: 1.0
            }
        },
        Transition {
            from: "active"
            SequentialAnimation {
                PropertyAction {
                    targets: [contentItem]
                    property: "opacity"
                    value: 1.0
                }
                PauseAnimation {
                    duration: 2450
                }
                NumberAnimation {
                    targets: [contentItem]
                    property: "opacity"
                    to: 0.0
                }
            }
        }
    ]
}
