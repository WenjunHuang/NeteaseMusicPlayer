import QtQuick 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls 2.13
import QtGraphicalEffects 1.13
import MusicPlayer 1.0
import "../../utils"
import "../../styles/variables.mjs" as Vars

Pane {
    id: root
    padding: Vars.spacingX2

    //radius: Vars.border_radius
    function categoryImage(category) {
        return "ruby"
    }

    SongCategoryListViewModel {
        id: viewModel
        onStateChanged: {
            console.log(viewModel.state.kind)
            if (state.kind === StateKinds.UnInit
                    || state.kind === StateKinds.Loading) {
                // show loading
                content.sourceComponent = loading
            }
            if (state.kind === StateKinds.Ready) {
                // show ready
                content.sourceComponent = ready
                console.log(viewModel.state)
            }
            if (state.kind === StateKinds.Error) {

                // show error
            }
        }
    }

    contentItem: Loader {
        id: content
        //        Behavior on width {
        //            NumberAnimation {
        //                duration: 200
        //            }
        //        }

        //        Behavior on height {
        //            NumberAnimation {
        //                duration: 200
        //            }
        //        }
    }

    Component {
        id: loading
        ColumnLayout {
            BusyIndicator {}
            Text {
                text: "正在加载中"
            }
        }
    }

    Component {
        id: ready
        ColumnLayout {
            spacing: Vars.spacingX4
            Repeater {
                model: viewModel.state.data.categories
                RowLayout {
                    spacing: Vars.spacingX5

                    Text {
                        //Layout.preferredWidth: 100
                        Layout.alignment: Qt.AlignTop
                        text: modelData.name
                    }

                    GridLayout {
                        columns: 6
                        columnSpacing: Vars.spacingX2
                        rowSpacing: Vars.spacingX2
                        Repeater {
                            model: modelData.items
                            Control {
                                Layout.preferredWidth: 60
                                Text {
                                    id: item
                                    text: modelData.name
                                    color: hovered? Material.primaryColor:Material.foreground
                                }
                                hoverEnabled: true
                            }
                        }
                    }
                }
            }
        }
    }

    states: [
        State {
            name: "loadingState"
            PropertyChanges {
                target: object
            }
        }
    ]
    background: Rectangle {
        //anchors.fill: parent
        id: body
        radius: Vars.border_radius
        //visible: false
    }
}
