import QtQuick 2.12
import QtQuick.Layouts 1.13
import QtQuick.Controls.Material 2.12
import "../styles/variables.mjs" as Vars
import FontAwesome 1.0

// 分页控件
Item {
    id: root

    property int total

    property int limit
    property int offset

    property int pageItemRadius: 3
    property int pageItemSize: 24

    property int columnCount: 10

    property int selectedPage: Math.floor(offset / limit) + 1
    property int totalPageCount: Math.ceil(total / limit)

    signal pageChanged(int xOffset, int xLimit)

    function pageForIndex(index) {
        if (selectedPage < columnCount - 1) {

        }

        return {
            "text": index + 1
        }
    }

    function createPageModel() {
        let result = []
        if (totalPageCount <= columnCount) {
            //let i = 1
            for (let i = 1; i <= totalPageCount; i++) {
                let data = {
                    text: i,
                    selected: i === selectedPage,
                    click: function () {
                        console.log("onClick")
                        if (i !== selectedPage)
                            pageChanged((i - 1) * limit, limit)
                    }
                }
                result.push(data)
            }
            return result
        }

        const distanceFromBegin = selectedPage - 1
        const distanceToEnd = totalPageCount - selectedPage
        if (distanceFromBegin < distanceToEnd) {
            // 最后一个是totalPageCount，倒数第二个是...
            if (selectedPage > columnCount - 3) {
                // 距离page 1的距离已经超出范围，那么第一个是1，第二个是...
                result = [{
                              "text": 1,
                              "selected": 1 === selectedPage,
                              "click": function () {
                                  pageChanged(0, limit)
                              }
                          }, {
                              "text": "..."
                          }]
                let selectedPageIndex = 3 + Math.floor((columnCount - 4) / 2)
                let i = 3
                for (; i <= columnCount - 2; i++) {
                    let page = selectedPage + i - selectedPageIndex
                    result.push({
                                    "text": page,
                                    "selected": page === selectedPage,
                                    "click": function () {
                                        if (page !== selectedPage) {
                                            pageChanged((page - 1) * limit,
                                                        limit)
                                        }
                                    }
                                })
                }
            } else {
                let i = 1
                for (; i <= columnCount - 2; i++)
                    result.push({
                                    "text": i,
                                    "selected": i === selectedPage,
                                    "click": function () {
                                        if (i !== selectedPage)
                                            pageChanged((i - 1) * limit, limit)
                                    }
                                })
            }
            result.push({
                            "text": "..."
                        }, {
                            "text": totalPageCount,
                            "click": function () {
                                pageChanged((totalPageCount - 1) * limit, limit)
                            }
                        })
        }
    }

    implicitWidth: layout.implicitWidth
    implicitHeight: layout.implicitHeight
    RowLayout {
        id: layout
        spacing: Vars.spacing_third
        Rectangle {
            radius: pageItemRadius
            Layout.preferredWidth: pageItemSize
            Layout.preferredHeight: pageItemSize
            Border {
                radius: pageItemRadius
                commonBorderWidth: 1
                borderColor: Material.frameColor
            }
            FAIcon {
                icon: FAIcons.faAngleLeftLight
                anchors.centerIn: parent
            }
        }
        Repeater {
            model: createPageModel()
            Rectangle {
                Component.onCompleted: {
                    console.log(modelData.click)
                }

                radius: pageItemRadius
                Layout.preferredWidth: pageItemSize
                Layout.preferredHeight: pageItemSize
                color: modelData.selected ? Material.accentColor : Material.backgroundColor

                Border {
                    radius: pageItemRadius
                    commonBorderWidth: 1
                    borderColor: Material.frameColor
                }
                Text {
                    anchors.centerIn: parent
                    text: modelData.text
                    color: modelData.selected ? Material.primaryHighlightedTextColor : Material.primaryTextColor
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    visible: modelData.click !== undefined ? true : false
                    onClicked: {
                        modelData.click()
                    }
                }
            }
        }

        Rectangle {
            radius: pageItemRadius
            Layout.preferredWidth: pageItemSize
            Layout.preferredHeight: pageItemSize
            Border {
                radius: pageItemRadius
                commonBorderWidth: 1
                borderColor: Material.frameColor
            }
            FAIcon {
                icon: FAIcons.faAngleRightLight
                anchors.centerIn: parent
            }
        }
    }
}
