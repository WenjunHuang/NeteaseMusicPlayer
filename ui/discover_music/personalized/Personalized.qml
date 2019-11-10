import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import "../../styles/variables.mjs" as Vars

Item {
    id: root
    ScrollView {
        id:scroll
        anchors.fill: parent
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        contentHeight: layout.height


        ColumnLayout {
            id:layout
            //minimumWidth: Vars.content_minimum_width
            //maximumWidth: Vars.content_maximum_width
            width: root.width
            BannerCarousel {
                Layout.minimumWidth: Vars.content_minimum_width
                Layout.maximumWidth: Vars.content_maximum_width
                Layout.alignment: Qt.AlignCenter
                height: 240
            }
            RecommendationSongLists {
                Layout.minimumWidth: Vars.content_minimum_width
                Layout.maximumWidth: Vars.content_maximum_width
                Layout.alignment: Qt.AlignCenter
            }

            PersonalizedNewSongs {
                Layout.minimumWidth: Vars.content_minimum_width
                Layout.maximumWidth: Vars.content_maximum_width
                Layout.alignment: Qt.AlignCenter
            }
        }
    }
}
