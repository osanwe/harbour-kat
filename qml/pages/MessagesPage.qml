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
import "../views"
import "../js/auth.js" as AuthJS
import "../js/storage.js" as StorageJS
import "../js/api/messages.js" as MessagesAPI
import "../js/api/users.js" as UsersAPI


Page {
    id: startPage

    property int chatsCounter: 0
    property int dialogsOffset: 0

    function initialize() {
        if (!StorageJS.readSettingsValue("user_id")) {
            pageStack.push(Qt.resolvedUrl("LoginPage.qml"))
        } else {
            dialogsOffset = 0
            chatsCounter = 0
            loadingDialogsIndicator.running = true
            messagesList.footerItem.visible = false
            messagesList.model.clear()  // TODO: Oh, really?!
            MessagesAPI.getDialogs(dialogsOffset)
        }
    }

    function doMainMenuItem() {
        if (StorageJS.readSettingsValue("user_id")) {
            loadingDialogsIndicator.running = true
            messagesList.footerItem.visible = false
            messagesList.model.clear()  // TODO: Oh, really?!
            chatsCounter = 0
            dialogsOffset = 0
            MessagesAPI.getDialogs(dialogsOffset)
        } else {
            console.log("You have to sign in")
        }
    }

    function formDialogsList(io, title, message, dialogId, readState, isChat) {
        console.log(readState)
        message = message.replace(/<br>/g, " ")
        messagesList.model.append({ isDialog: true,
                                    out: io,
                                    avatarSource: "image://theme/icon-cover-message",
                                    nameOrTitle: title,
                                    previewText: message,
                                    itemId: dialogId,
                                    readState: readState,
                                    isOnline: false,
                                    isChat: isChat })
    }

    function updateDialogsList(index, avatarURL, fullname, online) {
        while (messagesList.model.get(parseInt(index, 10)+chatsCounter+dialogsOffset).isChat)
            chatsCounter += 1
        messagesList.model.setProperty(parseInt(index, 10) + chatsCounter+dialogsOffset,
                                       "avatarSource", avatarURL)
        messagesList.model.setProperty(parseInt(index, 10) + chatsCounter + dialogsOffset,
                                       "nameOrTitle", fullname)
        messagesList.model.setProperty(parseInt(index, 10) + chatsCounter + dialogsOffset,
                                       "isOnline", online)
    }

    function stopBusyIndicator() {
        messagesList.footerItem.visible = true
        loadingDialogsIndicator.running = false
    }

    BusyIndicator {
        id: loadingDialogsIndicator
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: true
    }

    SilicaListView {
        id: messagesList
        anchors.fill: parent
        anchors.bottomMargin: Theme.paddingMedium

        model: ListModel {}

        delegate: UserItem {}

        PullDownMenu {

            MenuItem {
                id: aboutItem
                text: "О программе"
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }

//            MenuItem {
//                id: settingsItem
//                text: "Настройки"
//                onClicked: doMainMenuItem()
//            }

            MenuItem {
                id: newMessageItem
                text: "Новое сообщение"
                onClicked: pageStack.push(Qt.resolvedUrl("NewMessagePage.qml"))
            }

            MenuItem {
                id: mainMenuItem
                text: "Обновить"
                onClicked: doMainMenuItem()
            }
        }

        header: PageHeader {
            title: "Сообщения"
        }

        footer: Button {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width / 3 * 2
            text: "Загрузить больше"

            onClicked: {
                loadingDialogsIndicator.running = true
                dialogsOffset = dialogsOffset + 20
                chatsCounter = 0
                MessagesAPI.getDialogs(dialogsOffset)
            }
        }

        VerticalScrollDecorator {}
    }

    onStatusChanged: if (status === PageStatus.Active) initialize()
    Component.onCompleted: StorageJS.initDatabase()
}


