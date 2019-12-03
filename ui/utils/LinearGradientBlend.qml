import QtQuick 2.13
import QtGraphicalEffects 1.13
import "../styles/variables.mjs" as Vars

Item {
    property Item target
    // 加入一点颜色混合，使得"播放数"文字能比较突出
    LinearGradient {
        id: gradient
        anchors.fill: target
        start: Qt.point(0, 0)
        end: Qt.point(0, 300)
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: Vars.box_selected_border_color
            }
            GradientStop {
                position: 0.3
                color: "white"
            }
        }
        visible: false
    }

    Blend {
        anchors.fill: target
        source: target
        foregroundSource: gradient
        mode: "darken"
    }

}
