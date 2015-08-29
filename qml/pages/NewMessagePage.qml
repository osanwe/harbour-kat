/*
  Copyright (C) 2015 Petr Vytovtov
  Contact: Petr Vytovtov <osanwe@protonmail.ch>
  All rights reserved.

  This file is part of Kat.

  Kat is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Kat is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Kat.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import "../js/api/messages.js" as MessagesAPI

Dialog {
    id: newMessageDialog

    property Item contextMenu

    function updateSearchContactsList(uid, name, photo, isOnline) {
        searchContactsList.model.append({ uid:      uid,
                                          name:     name,
                                          photo:    photo,
                                          isOnline: isOnline })
    }

    function sendNewMessage() {
        if (currentContactsList.model.count === 1) {
            MessagesAPI.api_sendMessage(false,
                                    currentContactsList.model.get(0).uid,
                                    newMessageText.text,
                                    true)
        } else if (currentContactsList.model.count > 1) {
            var ids = ""
            var index = 0
            while (index < currentContactsList.model.count) {
                ids = ids + "," + currentContactsList.model.get(index).uid
                index = index + 1
            }
            ids = ids.substring(1)
            MessagesAPI.api_createChat(ids, newMessageText.text)
        }
    }

    DialogHeader {
        id: newMessageHeader
        acceptText: currentContactsList.model.count > 1 ? qsTr("Создать") : qsTr("Написать")
        cancelText: qsTr("Отменить")
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
            placeholderText: qsTr("Найти контакт")

            onTextChanged: {
                searchContactsList.model.clear()
                MessagesAPI.api_searchDialogs(text)
            }
        }

        model: ListModel {
            Component.onCompleted: {
                clear()
                MessagesAPI.api_searchDialogs("")
            }
        }

        delegate: BackgroundItem {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: Theme.paddingLarge
            anchors.rightMargin: Theme.paddingLarge
            height: Theme.itemSizeSmall

            Row {
                anchors.fill: parent
                spacing: 6

                Switch {
                    height: contactName.height
                    width: height
                    automaticCheck: false
                    checked: isOnline
                }

                Label {
                    id: contactName
                    text: name
                }
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
                if (index !== -1) currentContactsList.model.append({ uid:         uid,
                                                                     photoSource: photo })
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
                        contextMenu = contextMenuComponent.createObject(currentContactsList,
                                                                        { index: index })
                    contextMenu.show(myListItem)
                }
            }
        }

        Component {
            id: contextMenuComponent

            ContextMenu {

                property string index

                MenuItem {
                    text: qsTr("Удалить")
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
        placeholderText: {
            switch (currentContactsList.model.count) {
            case 0:
                return qsTr("Сообщение или название чата:")

            case 1:
                return qsTr("Сообщение:")

            default:
                return qsTr("Название чата:")
            }
        }
        label: {
            switch (currentContactsList.model.count) {
            case 0:
                return qsTr("Сообщение или название чата")

            case 1:
                return qsTr("Сообщение")

            default:
                return qsTr("Название чата")
            }
        }
    }

    onAccepted: sendNewMessage()
}
