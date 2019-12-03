import QtQuick 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls 2.13
import QtQuick.Controls.Material 2.13
import QtGraphicalEffects 1.13
import MusicPlayer 1.0
import FontAwesome 1.0
import "../../utils"
import "../../styles/variables.mjs" as Vars

Popup {
    id: root
    property var modelData
    property string currentSelectedCategoryName
    function categoryImage(category) {
        if (category === 0)
            return FAIcons.faGlobeLight
        if (category === 1)
            return FAIcons.faPianoKeyboardLight
        if (category === 2)
            return FAIcons.faCoffeeLight
        if (category === 3)
            return FAIcons.faSmileBeamLight
        if (category === 4)
            return FAIcons.faBusSchoolLight

        return FAIcons.faBusSchoolLight
    }
    Pane {
        padding: Vars.spacingX2

        contentItem: ColumnLayout {
            spacing: Vars.spacingX4
            Repeater {
                model: viewModel.state.data.categories
                RowLayout {
                    spacing: Vars.spacingX5

                    RowLayout {
                        Layout.fillWidth: false
                        Layout.alignment: Qt.AlignTop
                        spacing: Vars.spacing_third
                        FAIcon {
                            icon: categoryImage(modelData.category)
                        }

                        Text {
                            //Layout.preferredWidth: 100
                            Layout.alignment: Qt.AlignTop
                            text: modelData.name
                        }
                    }

                    GridLayout {
                        Layout.alignment: Qt.AlignTop
                        columns: 6
                        columnSpacing: Vars.spacingX2
                        rowSpacing: Vars.spacingX2
                        Repeater {
                            model: modelData.items
                            Control {
                                id: container
                                Layout.preferredWidth: 60
                                hoverEnabled: true
                                contentItem: Text {
                                    id: item
                                    text: modelData.name
                                    color: modelData.name === currentSelectedCategoryName ? Material.accentColor : (container.hovered ? Material.accentColor : Material.primaryTextColor)
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    cursorShape: Qt.PointingHandCursor
                                    onClicked: {
                                        currentSelectedCategoryName = modelData.name
                                        root.close()
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
