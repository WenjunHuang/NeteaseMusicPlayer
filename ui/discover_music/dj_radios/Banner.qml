import QtQuick 2.13
import QtQuick.Layouts 1.13
import MusicPlayer 1.0

import "../../utils"

Item {
    id:root
    DJBannerViewModel {
        id: viewModel
        onStateChanged: {
            console.log(state.kind)
            if (state.kind === StateKinds.Loading)
                layout.currentIndex = 0
            if (state.kind === StateKinds.Ready)
                layout.currentIndex = 1
        }
        Component.onCompleted: {
            viewModel.reload()
        }
    }

    StackLayout {
        id: layout
        anchors.fill:parent
        Loading{}
        Carousel{
            id:carousel
            model: viewModel.state.kind === StateKinds.Ready ? viewModel.state.data.bannerItems: []
        }
    }


}
