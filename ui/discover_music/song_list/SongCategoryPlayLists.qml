import QtQuick 2.13
import QtQuick.Layouts 1.13
import MusicPlayer 1.0
import "../../styles/variables.mjs" as Vars
import "../../utils"

ColumnLayout {
    SongCategoryPlayListsViewModel {
        id: viewModel
    }

    //    GridLayout {
    //        columns: 5
    //        columnSpacing: Vars.spacing
    //        rowSpacing: Vars.spacingX2
    //        Repeater {
    //            model: viewModel.state.data.playlists
    //        }
    //    }
    PagingSelector {
        Layout.fillWidth: false
        total: 200
        limit: 10
        offset: 0
        onOffsetChanged: {
            console.log(offset)
        }
    }
}
