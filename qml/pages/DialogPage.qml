import QtQuick 2.0
import Sailfish.Silica 1.0
import "../views"
import "../js/api/messages.js" as MessagesAPI

Page {
    id: dialogPage

    property string fullname
    property int dialogId
    property bool isChat

    function sendMessage() {
        console.log("Send: " + messageInput.text)
        MessagesAPI.sendMessage(isChat, dialogId, messageInput.text)
        messageInput.text = ""
    }

    function formMessagesList(io, readState, text) {
        text = text.replace(/<br>/g, "\n")
        messages.model.insert(0, {io: io, readState: readState, message: text} )
    }

    function scrollMessagesToBottom() {
        messages.positionViewAtEnd()
    }

    SilicaFlickable {
        anchors.fill: parent

    PageHeader {
        id: dialogTitle
        title: fullname
    }

    SilicaListView {
        id: messages
        anchors.fill: parent
        anchors.topMargin: dialogTitle.height
        anchors.bottomMargin: messageInput.height
        clip: true
        model: ListModel {}
        delegate: MessageItem {}
    }

    TextArea {
        id: messageInput
        width: parent.width
        anchors.bottom: parent.bottom
        placeholderText: "Сообщение:"
        label: "Сообщение:"

        EnterKey.enabled: text.length > 0
        EnterKey.iconSource: "image://theme/icon-m-enter-accept"
        EnterKey.onClicked: sendMessage()
    }

    PushUpMenu {
        MenuItem {
            text: "Обновить"
            onClicked: {
                messages.model.clear()
                MessagesAPI.getHistory(isChat, dialogId)
            }
        }
    }

    }

    onPageContainerChanged: MessagesAPI.getHistory(isChat, dialogId)
}
