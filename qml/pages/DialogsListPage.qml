import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: dialogsListPage

    SilicaListView {
        id: dialogsList
        anchors.fill: parent

        model: 10

        PullDownMenu {

            MenuItem {
                text: qsTr("Refresh")
            }

            MenuItem {
                text: qsTr("New message")
            }
        }

        header: PageHeader {
            title: qsTr("Dialogs")
        }

        delegate: BackgroundItem {
            id: dialogItem
            width: parent.width
            height: Theme.itemSizeMedium

            Image {
                id: dialogAvatar
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: Theme.horizontalPageMargin
                width: Theme.iconSizeMedium
                height: Theme.iconSizeMedium
            }

            Column {
                anchors.left: dialogAvatar.right
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: Theme.paddingMedium
                anchors.rightMargin: Theme.horizontalPageMargin

                Row {
                    width: parent.width
                    height: childrenRect.height
                    spacing: Theme.paddingMedium

                    Switch {
                        id: isOnline
                        height: name.height
                        width: height
                        automaticCheck: false
                    }

                    Label {
                        id: name
                        width: parent.width - isOnline.width - Theme.paddingMedium
                        color: dialogItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                        font.bold: true
                        truncationMode: TruncationMode.Fade
                    }
                }

                Label {
                    width: parent.width
                    color: dialogItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                    truncationMode: TruncationMode.Fade
                    text: modelData.lastMessage.body
                }
            }
        }

        VerticalScrollDecorator {}
    }

    Component.onCompleted: vksdk.messages.getDialogs()
}

