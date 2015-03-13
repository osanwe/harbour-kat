import QtQuick 2.0
import Sailfish.Silica 1.0
import "../views"
import "../js/api/messages.js" as MessagesAPI

Page {
    id: dialogPage

    property string fullname
    property int dialogId
    property bool isChat

    property int messagesOffset: 0

    function sendMessage() {
        console.log("Send: " + messageInput.text)
        MessagesAPI.sendMessage(isChat, dialogId, messageInput.text)
        messages.model.clear()
        messageInput.text = ""
        messagesOffset = 0
        MessagesAPI.getHistory(isChat, dialogId, messagesOffset)
    }

    function formMessagesList(io, readState, text) {
        text = text.replace(/<br>/g, "\n")
        messages.model.insert(0, {io: io, readState: readState, message: text} )
    }

    function scrollMessagesToBottom() {
        if (messagesOffset === 0)
            messages.positionViewAtEnd()
        else
            messages.positionViewAtIndex(49, ListView.Beginning)
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

            header: Button {
//                anchors.centerIn: parent
//                anchors.left: parent.left
//                anchors.right: parent.right
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width / 3 * 2
                text: "Загрузить больше"
                onClicked: { messagesOffset = messagesOffset + 50; MessagesAPI.getHistory(isChat, dialogId, messagesOffset) }
            }

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
                    messagesOffset = 0
                    MessagesAPI.getHistory(isChat, dialogId, messagesOffset)
                }
            }
        }

        VerticalScrollDecorator {}
    }

    Component.onCompleted: MessagesAPI.getHistory(isChat, dialogId, messagesOffset)
}
