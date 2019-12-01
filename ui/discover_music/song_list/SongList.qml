import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13
import "../../styles/variables.mjs" as Vars

Item {
    id:root
    property string currentCategoryName:"全部"
    ScrollView {
        id: scroll
        clip: true
        anchors.fill: parent
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        contentHeight: layout.height

        RowLayout {
            id: layout
            width: root.width
            spacing: 0
            Rectangle {
                Layout.minimumWidth: Vars.spacingX2
            }
            ColumnLayout{
                Layout.minimumWidth: Vars.content_minimum_width
                spacing: Vars.spacingX3
                Rectangle {
                    height: 0
                    Layout.fillWidth: true
                }

                HighQuality {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 170
                    categoryName:currentCategoryName
                }

                SongCategorySelector{
                    Layout.fillWidth: true

                }
            }

            Rectangle {
                Layout.minimumWidth: Vars.spacingX2
            }
        }
    }

}
