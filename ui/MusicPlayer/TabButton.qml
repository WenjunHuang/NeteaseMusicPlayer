import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Templates 2.13 as T
import QtQuick.Layouts 1.13
import "../styles/variables.mjs" as Vars

T.TabButton {
    id: control

    property bool selected: control.TabBar.tabBar.currentIndex === control.TabBar.index
    property Item badge

    font.pixelSize: Vars.font_size_lg
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)
    width: implicitWidth
    height: implichtHeight

    topPadding: Vars.spacingX2
    bottomPadding: Vars.spacingX2
    leftPadding: Vars.spacingX3
    rightPadding: Vars.spacingX3
    spacing: Vars.spacing_half

    contentItem: RowLayout {
        spacing: Vars.spacing_half

        Item {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
            visible: control.badge ? true : false
            children: control.badge ? [control.badge] : []
            implicitHeight: control.badge ? control.badge.implicitHeight : 0
            implicitWidth: control.badge ? control.badge.implicitWidth : 0
        }
        Text {
            Layout.alignment: Qt.AlignHCenter
            text: control.text
            font: control.font
            color: Vars.text_color
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
    }

    background: Rectangle {
        implicitHeight: Vars.tab_bar_height
        width: control.width
        height: control.height
        color: control.hovered ? Vars.tab_bar_hover_background_color : Vars.tab_bar_background_color
    }

    hoverEnabled: true
}
