import QtQuick 2.0
import Sailfish.Silica 1.0
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

    SilicaFlickable {
        anchors.fill: parent

        PageHeader { title: fullname }

        TextArea {
            id: messageInput
            width: parent.width
            anchors.bottom: parent.bottom
            placeholderText: "Сообщение:"
            label: "Сообщение:"

            EnterKey.enabled: text.length > 0
            EnterKey.onClicked: sendMessage()
        }
    }
}
