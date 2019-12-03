import QtQuick 2.12

Rectangle {
    property Item target:parent

    property bool commonBorder: true

    property int lBorderwidth: 0
    property int rBorderwidth: 0
    property int tBorderwidth: 0
    property int bBorderwidth: 0

    property int commonBorderWidth: 0

    z: -1

    property color borderColor: "transparent"

    color: borderColor

    anchors {
        left: target.left
        right: target.right
        top: target.top
        bottom: target.bottom

        topMargin: commonBorder ? -commonBorderWidth : -tBorderwidth
        bottomMargin: commonBorder ? -commonBorderWidth : -bBorderwidth
        leftMargin: commonBorder ? -commonBorderWidth : -lBorderwidth
        rightMargin: commonBorder ? -commonBorderWidth : -rBorderwidth
    }
}
