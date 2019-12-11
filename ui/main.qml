import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import MusicPlayer 1.0
import "./discover_music"
import "./styles/variables.mjs" as Vars

ApplicationWindow {
    visible: true
    minimumWidth: 1000
    minimumHeight: 670

    property int mainNavIndex

    SplitView {
        anchors.fill: parent
        MainNavigationBar {
            id: navigationBar
            SplitView.minimumWidth: 200
        }

        StackView {
            id: mainStackView
            SplitView.minimumWidth: Vars.content_minimum_width
            initialItem: mainStackViewInit
            popEnter: null
            popExit: null
            pushEnter: null
            pushExit: null
        }
    }

    Component {
        id: mainStackViewInit
        DiscoverMusic {
            currentIndex: 0
        }
    }

    //    DiscoverMusic{
    //        anchors.fill:parent
    //    }
}
