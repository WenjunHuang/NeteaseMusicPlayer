
import QtQuick 2.13
import QtQuick.Templates 2.13 as T
import Music 1.0

T.Button {
    id: control
    hoverEnabled: true
    opacity: enabled ? 1.0 : 0.6


    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                                         contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: StyleVariables.button_height
    leftPadding: StyleVariables.spacing
    rightPadding: StyleVariables.spacing

    background: Rectangle {
        id: buttonBackground
        implicitWidth: 100
        implicitHeight: 40
        color:(hovered && enabled)?StyleVariables.button_hover_background:StyleVariables.button_background
        border.color: StyleVariables.base_border_color
        border.width: StyleVariables.base_border_width
        radius: StyleVariables.button_border_radius
    }

    contentItem: Text {
        id: textItem
        text: control.text

        font{
            pixelSize: StyleVariables.font_size
        }
        color: StyleVariables.button_text_color
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight

        states: [
            State {
                name: "normal"
                when: !control.down
            },
            State {
                name: "down"
                when: control.down
                PropertyChanges {
                    target: textItem
                    color: Theme.mainColorDarker
                }
            }
        ]
    }
}