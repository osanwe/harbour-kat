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

    PageHeader { id: dialogTitle; title: fullname }

    SilicaListView {
        id: messages
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: dialogTitle.height
        anchors.bottomMargin: messageInput.height
//        anchors.top: dialogTitle.bottom
//        anchors.bottom: messageInput.top
        model: ListModel {}
        delegate: MessageItem {}
    }

    TextArea {
        id: messageInput
        width: parent.width
        anchors.bottom: parent.bottom
        placeholderText: "Сообщение:"
        label: "Сообщение:"

        onClicked: if (text.length === 0) messages.positionViewAtEnd()

        EnterKey.enabled: text.length > 0
        EnterKey.iconSource: "image://theme/icon-m-enter-next"
        EnterKey.onClicked: sendMessage()
    }

    onPageContainerChanged: MessagesAPI.getHistory(isChat, dialogId)
}
