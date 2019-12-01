import QtQuick 2.13
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.13

Item {
    id:root
    clip:true
    property real radius

    Rectangle {
        // 圆角遮罩
        id: mask
        width: root.width
        height: root.height
        radius: root.radius
        visible: false
    }

    layer.enabled: true
    layer.effect: OpacityMask {
        maskSource: mask
    }
}
