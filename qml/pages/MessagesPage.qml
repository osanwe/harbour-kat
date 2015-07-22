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

    function updateDialogs() {
        dialogsOffset = 0
        chatsCounter = 0
        loadingDialogsIndicator.running = true
        messagesList.footerItem.visible = false
        messagesList.model.clear()
        MessagesAPI.api_getDialogsList(dialogsOffset)
    }

    function formDialogsList(io, title, message, dialogId, readState, isChat) {
        console.log(readState)
        message = message.replace(/<br>/g, " ")
        messagesList.model.append({ isDialog:     true,
                                    out:          io,
                                    avatarSource: "image://theme/icon-cover-message",
                                    nameOrTitle:  title,
                                    previewText:  message,
                                    itemId:       dialogId,
                                    readState:    readState,
                                    isOnline:     false,
                                    isChat:       isChat })
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

        PullDownMenu {

            MenuItem {
                id: newMessageItem
                text: "Новое сообщение"
                onClicked: pageStack.push(Qt.resolvedUrl("NewMessagePage.qml"))
            }

            MenuItem {
                id: mainMenuItem
                text: "Обновить"
                onClicked: updateDialogs()
            }
        }

        header: PageHeader {
            title: "Сообщения"
        }

        model: ListModel {}

        delegate: UserItem {
            onClicked: {
                pageStack.push(Qt.resolvedUrl("../pages/DialogPage.qml"),
                               { "fullname":     nameOrTitle,
                                 "dialogId":     itemId,
                                 "isChat":       isChat,
                                 "isOnline":     isOnline,
                                 "avatarSource": avatarSource,
                                 "userAvatar":   "$XDG_CACHE_HOME/harbour-kat/" + StorageJS.readUserAvatar() })
            }
        }

        footer: Button {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width / 3 * 2
            text: "Загрузить больше"

            onClicked: {
                loadingDialogsIndicator.running = true
                dialogsOffset = dialogsOffset + 20
                chatsCounter = 0
                MessagesAPI.api_getDialogsList(dialogsOffset)
            }
        }

        VerticalScrollDecorator {}
    }

    onStatusChanged: if (status === PageStatus.Active) updateDialogs()
}


