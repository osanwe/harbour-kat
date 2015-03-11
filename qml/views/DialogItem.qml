import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    width: parent.width
    height: Theme.itemSizeMedium
    highlighted: io === 0 && readState === 0

    function loadDialogPage() {
        console.log("dialog id = " + dialogId)
        pageStack.push(Qt.resolvedUrl("../pages/DialogPage.qml"),
                       { "fullname": name.text, "dialogId": dialogId, "isChat": isChat })
    }

    Image {
        id: avatar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 5
        anchors.leftMargin: 10
        height: parent.height - 10
        width: height
        source: avatarSource
    }

    Row {
        anchors.top: avatar.top
        anchors.left: avatar.right
        anchors.topMargin: 5
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 5
        spacing: 6

        Switch {
            id: isUserOnline
            height: name.height
            width: height
            automaticCheck: false
            checked: isOnline
        }

        Label {
            id: name
            color: { readState === 0 && io === 0 ? Theme.highlightColor : Theme.primaryColor }
            text: nameOrTitle
            truncationMode: TruncationMode.Fade
            font.bold: true
        }
    }

    Label {
        id: messagePreview
        anchors.bottom: avatar.bottom
        anchors.left: avatar.right
        anchors.bottomMargin: 5
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 5
        color: { readState === 1 ? Theme.secondaryColor : Theme.secondaryHighlightColor }
        text: lastMessage
        truncationMode: TruncationMode.Fade
    }

    onClicked: loadDialogPage()
}
