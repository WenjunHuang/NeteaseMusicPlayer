import QtQml 2.13
import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import MusicPlayer 1.0
import "../../styles/variables.mjs" as Vars
import "../../utils"

Item {
    id: root

    BannerViewModel {
        id: viewModel
        onStateChanged: {
            if (state.kind === StateKinds.Loading)
                layout.currentIndex = 0

            if (state.kind === StateKinds.Ready)
                layout.currentIndex = 1
        }
    }

    StackLayout {
        id: layout
        anchors.fill: parent
        Loading {
        }
        Carousel {
            id: carousel
            model: viewModel.state.kind === StateKinds.Ready ? viewModel.state.data.bannerItems:[]
        }
    }
}
