import QtQuick 2.0
import Sailfish.Silica 1.0
import "../js/api/messages.js" as MessagesAPI

Dialog {
    id: newMessageDialog
//    anchors.fill: parent

    function updateSearchContactsList(name) {
        searchContactsList.model.append({ name: name })
    }

    DialogHeader {
        id: newMessageHeader
        acceptText: "Написать"
        cancelText: "Отменить"
    }

    SilicaListView {
        id: searchContactsList
        anchors.fill: parent
        anchors.topMargin: newMessageHeader.height
        clip: true

        currentIndex: -1
        header: SearchField {
            width: parent.width
            placeholderText: "Добавить контакт"

            onTextChanged: { searchContactsList.model.clear(); MessagesAPI.searchDialogs(text) }
        }

        model: ListModel {}

        delegate: BackgroundItem {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: Theme.paddingLarge
            anchors.rightMargin: Theme.paddingLarge
            height: Theme.itemSizeSmall
//            width: parent.width - 2 * Theme.paddingMedium

            Label {
                anchors.fill: parent
                text: name
            }

            onClicked: console.log(name)
        }
    }

//    SilicaListView {
//        //
//    }

    TextArea {
        id: newMessageText
        anchors.bottom: parent.bottom
        width: parent.width
        placeholderText: "Сообщение:"
        label: "Сообщение:"
    }

    onAccepted: console.log("Posting...")
    onRejected: console.log("Canceling...")
}
