import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.13
import QtQuick.Shapes 1.13
import QtGraphicalEffects 1.13

import MusicPlayer 1.0
import "../styles/variables.mjs" as Vars
import "../utils"

Item {
    id: root

    property var model: []
    property double itemWidth: 540
    property double itemHeight: 200
    property double radius: 7

    Component {
        id: appDelegate
        RoundCorner {
            radius: root.radius
            width: root.itemWidth
            height: root.itemHeight
            scale: PathView.iconScale
            opacity: PathView.iconOpacity
            z: PathView.iconZorder
            anchors.verticalCenter: view.verticalCenter
            FadeInImage {
                id: fadeInImage
                anchors.fill: parent
                contentItem: Image {
                    id: myIcon
                    source: modelData.imageUrl
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectCrop
                    sourceSize: Qt.size(myIcon.width,myIcon.height)
                    onStatusChanged: {
                        if (myIcon.status === Image.Ready)
                            fadeInImage.contentLoaded()
                    }
                    Shape {
                        id: shape
                        anchors.right: myIcon.right
                        anchors.bottom:myIcon.bottom
                        width: typeTitle.width + 2 * Vars.spacing_half + 2 * root.radius
                        height: typeTitle.height + 2 * Vars.spacing_half
                        ShapePath {
                            startX: 0
                            startY: root.radius
                            fillColor: Material.accentColor
                            strokeColor: "transparent"
                            PathArc {
                                x: root.radius
                                y: 0
                                radiusX: root.radius; radiusY: root.radius
                                useLargeArc: false
                            }
                            PathLine {
                                x: shape.width
                                y: 0
                            }
                            PathLine {
                                x: shape.width
                                y: shape.height - root.radius
                            }
                            PathArc {
                                x: shape.width - root.radius
                                y: shape.height
                                radiusX: root.radius; radiusY: root.radius
                                useLargeArc: false
                            }
                            PathLine {
                                x: 0
                                y: shape.height
                            }
                            PathLine {
                                x: 0
                                y: root.radius
                            }
                        }
                    }
                    Text {
                        id: typeTitle
                        anchors.centerIn: shape
                        anchors {
                            bottom: myIcon.bottom
                            right: myIcon.right
                        }
                        text: modelData.typeTitle
                        font.pixelSize: Vars.font_size_sm
                        color: "white"
                    }
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: view.currentIndex = index
            }
        }
    }

    PathView {
        id: view
        anchors.bottom: pageIndicator.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        clip: true
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        model: root.model
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
        count: root.model.length
        currentIndex: view.currentIndex
        delegate: Rectangle {
            id: indicatorDelegate
            implicitWidth: 8
            implicitHeight: 8

            radius: width / 2
            color: Material.accentColor

            opacity: index === pageIndicator.currentIndex ? 0.95 : pressed ? 0.7 : 0.3

            Behavior on opacity {
                OpacityAnimator {
                    duration: 100
                }
            }

            //            MouseArea {
            //                anchors.fill: indicatorDelegate
            //                hoverEnabled: true
            //                onEntered: {
            //                    pageIndicator.currentIndex = index
            //                }
            //            }
        }
    }

    //    MouseArea {
    //        id: hoverDectector
    //        anchors.fill: parent
    //        propagateComposedEvents: true
    //        hoverEnabled: true
    //    }
    Timer {
        id: timer
        interval: 2000
        repeat: true
        running: true
        //running: !hoverDectector.containsMouse
        onTriggered: {
            pageIndicator.currentIndex = (pageIndicator.currentIndex + 1) % pageIndicator.count
        }
    }
}
