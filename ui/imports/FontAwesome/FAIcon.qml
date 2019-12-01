import QtQuick 2.13

Text {
    id:root
    property var icon
    property alias size: root.font.pixelSize
    font.family: icon.family
    font.weight: icon.weight
    text: icon.code
}
