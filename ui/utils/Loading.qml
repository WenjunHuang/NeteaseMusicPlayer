import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import "../styles/variables.mjs" as Vars

Item {
    id: root
    implicitHeight: layout.implicitHeight
    implicitWidth: layout.implicitWidth
    RowLayout {
        id: layout
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        BusyIndicator {
            width: 24
            height: 24
        }
        Text {
            text: "加载中..."
            font.pixelSize: Vars.font_size_sm
        }
    }
}
