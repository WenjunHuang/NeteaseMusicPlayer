import QtQuick 2.13
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.13
import MusicPlayer 1.0
import "../../styles/variables.mjs" as Vars

Item {
    id: root

    BannerViewModel{
        id: viewModel
    }

    Component {
        id: appDelegate
        Item {
            width: myIcon.width
            height: myIcon.height
            scale: PathView.iconScale
            opacity: PathView.iconOpacity
            z: PathView.iconZorder
            anchors.verticalCenter: view.verticalCenter
            Rectangle {
                id: mask
                width: myIcon.width
                height: myIcon.height

                radius: 7
                border.color: "black"
                border.width: 2
                visible: false
            }
            Item {
                width: myIcon.width
                height: myIcon.height

                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: mask
                }
                Image {
                    width: 540
                    height: 200
                    id: myIcon
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: imageUrl
                }
                Text {
                    anchors {
                        bottom: myIcon.bottom
                        right: myIcon.right
                    }
                    //text: parent.PathView.isCurrentItem ? name + " yes" : name
                    text: typeTitle
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: view.currentIndex = index
            }
        }
    }

    Component {
        id: appHighlight
        Rectangle {
            width: 50
            height: 50
            color: "lightsteelblue"
        }
    }

    PathView {
        id: view
        anchors.bottom: pageIndicator.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        model: viewModel.banners
        delegate: appDelegate
        snapMode: PathView.SnapToItem
        currentIndex: pageIndicator.currentIndex
        path: Path {
            startX: 0
            startY: 0
            PathAttribute {
                name: "iconScale"
                value: 0.5
            }
            PathAttribute {
                name: "iconOpacity"
                value: 0.3
            }
            PathAttribute {
                name: "iconZorder"
                value: 0
            }

            PathLine {
                x: view.width / 2
                y: 0
            }

            PathAttribute {
                name: "iconScale"
                value: 1.0
            }
            PathAttribute {
                name: "iconOpacity"
                value: 1.0
            }
            PathAttribute {
                name: "iconZorder"
                value: 9999
            }
            PathLine {
                x: view.width
                y: 0
            }
            PathAttribute {
                name: "iconScale"
                value: 0.5
            }
            PathAttribute {
                name: "iconOpacity"
                value: 0.3
            }

            PathAttribute {
                name: "iconZorder"
                value: 0
            }
        }
    }
    PageIndicator {
        id: pageIndicator
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        interactive: true
        count: viewModel.bannerCount
        currentIndex: view.currentIndex
    }
}
