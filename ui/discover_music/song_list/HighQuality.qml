import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import QtGraphicalEffects 1.13
import MusicPlayer 1.0
import FontAwesome 1.0
import "../../styles/variables.mjs" as Vars
import "../../utils"

Item {
    id: root
    property alias categoryName: viewModel.categoryName
    SongListHighQualityViewModel {
        id: viewModel
        onStateChanged: {
            console.log(state.kind)
            if (state.kind === StateKinds.UnInit
                    || state.kind === StateKinds.Loading) {
                //loader.sourceComponent = loading
                root.data = [loading.createObject(root)]
            }
            if (state.kind === StateKinds.Ready) {
                root.data = [ready.createObject(root, {
                                                    "name": state.data.name,
                                                    "copywriter": state.data.copywriter,
                                                    "coverImgUrl": state.data.coverImgUrl
                                                })]
            }
        }
    }

    Loader {
        id: loader
        anchors.fill: parent
    }

    Component {
        id: loading
        ColumnLayout {
            anchors.centerIn: parent
            BusyIndicator {}
            Text {
                text: "加载中..."
            }
        }
    }

    Component {
        id: ready
        Item {
            property string name
            property string copywriter
            property url coverImgUrl
            anchors.fill: parent

            RoundCorner {
                id: background
                anchors.fill: parent
                radius: Vars.border_radius_large
                Component.onCompleted: {
                    console.log()
                }

                Image {
                    id: backgroundImage
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectCrop
                    visible: false
                    source: coverImgUrl
                }
                FastBlur {
                    id: backgroundImageBlur
                    anchors.fill: backgroundImage
                    source: backgroundImage
                    visible: false
                    radius: 64
                }
                BrightnessContrast {
                    anchors.fill: backgroundImage
                    source: backgroundImageBlur
                    brightness: 0.1
                }
            }

            RoundCorner {
                id: titleImage
                radius: Vars.border_radius
                width: 140
                height: 140
                anchors.left: background.left
                anchors.top: background.top
                anchors.bottom: background.bottom
                anchors.leftMargin: 14
                anchors.topMargin: 14
                anchors.bottomMargin: 14

                Image {
                    anchors.fill: parent
                    source: coverImgUrl
                }
            }

            Rectangle {
                id: highQualityRect
                anchors.left: titleImage.right
                anchors.leftMargin: Vars.spacing
                anchors.top: titleImage.top
                anchors.topMargin: Vars.spacingX2
                height: highQualityName.height + 2 * Vars.spacing
                width: highQualityName.width + height
                radius: height / 2
                color:"transparent"
                border.color: "#E6A961"
                border.width: 1
//                Border {
//                    commonBorderWidth: 1
//                    borderColor: "#E6A961"
//                    radius: height / 2
//                }
                RowLayout {
                    id: highQualityName
                    anchors.centerIn: parent
                    spacing: Vars.spacing_third
                    FAIcon {
                        Layout.alignment: Qt.AlignVCenter
                        icon: FAIcons.faCrownLight
                        color:"#E6A961"
                        size: 14
                    }
                    Text {
                        Layout.alignment: Qt.AlignVCenter
                        font.pixelSize: 12
                        color: "#E6A961"
                        text: "精品歌单"
                    }
                }
            }

            Text {
                id: highQualityNameText
                anchors.left: titleImage.right
                anchors.leftMargin: Vars.spacing
                anchors.top: highQualityRect.bottom
                anchors.topMargin: Vars.spacingX2
                text: name
                font.pixelSize: 16
                color:"white"
            }

            Text{
                id: highQualityCopywriterText
                anchors.left: titleImage.right
                anchors.leftMargin: Vars.spacing
                anchors.top: highQualityNameText.bottom
                anchors.topMargin: Vars.spacing_half
                text: copywriter
                font.pixelSize: 11
                color: Qt.rgba(1,1,1,0.3)
            }
        }

    }
}
