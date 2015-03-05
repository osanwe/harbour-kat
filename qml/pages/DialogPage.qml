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

    function formMessagesList(text) {
        text = text.replace(/<br>/g, "\n")
        messages.model.insert(0, {message: text} )
    }

    PageHeader { id: dialogTitle; title: fullname }

    SilicaListView {
        id: messages
        width: parent.width
        anchors.top: dialogTitle.bottom
        anchors.bottom: messageInput.top
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
        EnterKey.onClicked: sendMessage()
    }

    onPageContainerChanged: MessagesAPI.getHistory(isChat, dialogId)
}
