import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: aboutPage

    SilicaFlickable {
        anchors.fill: parent

        PageHeader {
            id: versionLabel
            title: "vkFish v0.1"
        }

        Label {
            id: shortInfo
            anchors.top: versionLabel.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - 30
            textFormat: Text.StyledText
            linkColor: Theme.highlightColor
            text: "Неофициальный клиент для социальной сети ВКонтакте, разрабатываемый силами <a href=\"https://udmlug.wordpress.com/\">Linux User Group Удмуртия</a> и распространяемый под лицензией GNU GPLv3."
            wrapMode: TextEdit.Wrap

            onLinkActivated: Qt.openUrlExternally(link)
        }

        SilicaListView {
            anchors.fill: parent
            anchors.topMargin: versionLabel.height + shortInfo.height
            width: parent.width
            clip: true

            model: ListModel {

                ListElement {
                    developerInfo: "<a href=\"https://twitter.com/Osanwe\">Ósanwe</a>"
                }

                ListElement {
                    developerInfo: "<a href=\"https://m.vk.com/nostariel\">Nostariel</a>"
                }
            }

            delegate: Item {
                height: Theme.itemSizeSmall
                width: parent.width

                Label {
                    id: developerName
                    anchors.centerIn: parent
                    textFormat: Text.StyledText
                    linkColor: Theme.highlightColor
                    text: developerInfo

                    onLinkActivated: Qt.openUrlExternally(link)
                }
            }
        }
    }
}
