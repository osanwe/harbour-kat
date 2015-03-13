import QtQuick 2.0
import Sailfish.Silica 1.0
import "../js/api/messages.js" as MessagesAPI

Dialog {
    id: newMessageDialog

    property Item contextMenu

    function updateSearchContactsList(uid, name, photo) {
        searchContactsList.model.append({ uid: uid, name: name, photo: photo })
    }

    function sendNewMessage() {
        if (currentContactsList.model.count === 1) {
            MessagesAPI.sendMessage(false, currentContactsList.model.get(0).uid, newMessageText.text)
        } else {
            var ids = ""
            var index = 0
            while (index < currentContactsList.model.count) {
                ids = ids + "," + currentContactsList.model.get(index).uid
                index = index + 1
            }
            ids = ids.substring(1)
            MessagesAPI.sendGroupMessage(ids, newMessageText.text)
        }
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
        anchors.bottomMargin: newMessageText.height + currentContactsList.height
        clip: true

        currentIndex: -1
        header: SearchField {
            width: parent.width
            placeholderText: "Добавить контакт"

            onTextChanged: { searchContactsList.model.clear(); MessagesAPI.searchDialogs(text) }
        }

        model: ListModel {
            Component.onCompleted: { clear(); MessagesAPI.searchDialogs("") }
        }

        delegate: BackgroundItem {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: Theme.paddingLarge
            anchors.rightMargin: Theme.paddingLarge
            height: Theme.itemSizeSmall

            Label {
                anchors.fill: parent
                text: name
            }

            onClicked: {
                console.log(uid + " | " + name)
                var index = 0
                while (index < currentContactsList.model.count) {
                    if (uid === currentContactsList.model.get(index).uid) {
                        index = -1
                        break
                    }
                    index = index + 1
                }
                if (index !== -1) currentContactsList.model.append({ uid: uid, photoSource: photo })
            }
        }
    }

    SilicaListView {
        id: currentContactsList

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: Theme.paddingLarge
        anchors.rightMargin: Theme.paddingLarge
        anchors.bottom: newMessageText.top
        height: {
            if (model.count > 0)
                return contextMenu ? contextMenu.height + Theme.itemSizeMedium : Theme.itemSizeMedium
            else
                return 0
        }

//        height: contextMenu ? contextMenu.height + Theme.itemSizeMedium : Theme.itemSizeMedium
        spacing: 6
        clip: true
        orientation: ListView.Horizontal

        model: ListModel {}

        delegate: Item {
            id: myListItem

            property bool menuOpen: contextMenu != null && contextMenu.parent === myListItem

            height: menuOpen ? contextMenu.height + contentItem.height : contentItem.height
            width: Theme.itemSizeMedium

            BackgroundItem {
                id: contentItem
                height: Theme.itemSizeMedium
                width: height

                Image {
                    id: contactAvatar
                    anchors.fill: parent
                    source: photoSource
                }

                onPressAndHold: {
                    console.log(index)
                    if (!contextMenu)
                        contextMenu = contextMenuComponent.createObject(currentContactsList, {index: index})
                    contextMenu.show(myListItem)
                }
            }
        }

        Component {
            id: contextMenuComponent

            ContextMenu {

                property string index

                MenuItem {
                    text: "Удалить"
                    onClicked: currentContactsList.model.remove(index)
                }

                onClosed: contextMenu = null
            }
        }
    }

    TextArea {
        id: newMessageText
        anchors.bottom: parent.bottom
        width: parent.width
        placeholderText: "Сообщение:"
        label: "Сообщение:"
    }

    onAccepted: { console.log("Posting..."); sendNewMessage() }
    onRejected: console.log("Canceling...")
}
