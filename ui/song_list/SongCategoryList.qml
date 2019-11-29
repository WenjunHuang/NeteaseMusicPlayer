import QtQuick 2.13
import QtQuick.Layouts 1.13
import QtQuick.Controls 2.13
import MusicPlayer 1.0
import "../utils"
import "../styles/variables.mjs" as Vars

RoundCorner {
    SongCategoryListViewModel {
        id: viewModel
        onStateChanged: {
            if (state.kind === SongCategoryListViewModel.Loading) {
                // show loading
                content.sourceComponent = loading
            }
            if (state.kind === SongCategoryListViewModel.Ready) {

                // show ready
            }
            if (state.kind === SongCategoryListViewModel.Error) {

                // show error
            }
        }
    }

    Behavior on width {
        NumberAnimation{duration:200}
    }

    Behavior on height {
        NumberAnimation{duration:200}
    }

    Loader {
        id: content
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
        RowLayout {
            spacing: Vars.spacingX3
            Repeater {
                model: viewModel.state.items
                RowLayout {
                    Item {
                        Text{
                            text:name
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
}
