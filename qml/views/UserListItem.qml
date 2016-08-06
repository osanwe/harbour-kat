import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: userListItem
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: Theme.horizontalPageMargin
    anchors.rightMargin: Theme.horizontalPageMargin
    height: Theme.itemSizeMedium

    property var isUser
    property alias avatarSource: avatar.source
    property alias onlineStatus: online.checked
    property alias titleText: title.text
    property alias bodyText: body.text

    Row {
        width: parent.width
        height: parent.height
        spacing: Theme.paddingMedium

        Image {
            id: avatar
            anchors.verticalCenter: parent.verticalCenter
            width: Theme.iconSizeMedium
            height: Theme.iconSizeMedium
            fillMode: Image.PreserveAspectFit
        }

        Column {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - avatar.width - Theme.paddingMedium
            height: parent.height
            spacing: Theme.paddingMedium

            Row {
                width: parent.width
                spacing: Theme.paddingMedium

                Switch {
                    id: online
                    width: title.height
                    height: title.height
                    automaticCheck: false
                    visible: isUser
                }

                Label {
                    id: title
                    width: parent.width - online.width - Theme.paddingMedium
                    color: userListItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    truncationMode: TruncationMode.Fade
                    font.bold: true
                }
            }

            Label {
                id: body
                width: parent.width
                color: userListItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                truncationMode: TruncationMode.Fade
            }
        }
    }
}

