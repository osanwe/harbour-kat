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
import "../js/storage.js" as StorageJS
import "../js/api/messages.js" as MessagesAPI
import "../js/api/users.js" as UsersAPI

Page {
    id: dialogPage

    property string fullname
    property int dialogId
    property bool isChat
    property bool isOnline
    property string avatarSource
    property string userAvatar

    property int messagesOffset: 0

    function sendMessage() {
        MessagesAPI.sendMessage(isChat, dialogId, messageInput.text, false)
        messages.model.clear()
        messageInput.text = ""
        messagesOffset = 0
    }

    function formMessagesList(io, readState, text) {
        text = text.replace(/<br>/g, "\n")
        messages.model.insert(0, {io: io, readState: readState, message: text, avatarSource: avatarSource, userAvatar: userAvatar } )
    }

    function scrollMessagesToBottom() {
        if (messagesOffset === 0)
            messages.positionViewAtEnd()
        else
            messages.positionViewAtIndex(49, ListView.Beginning)
    }

    function stopLoadingMessagesIndicator() {
        loadingMessagesIndicator.running = false
    }

    function setUserAvatar(source) {
        userAvatar = source
    }

    BusyIndicator {
        id: loadingMessagesIndicator
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: true
    }

    SilicaFlickable {
        anchors.fill: parent

        Label {
            id: dialogTitle
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: Theme.paddingLarge
            font.pixelSize: Theme.fontSizeLarge
            color: Theme.highlightColor
            height: Theme.fontSizeLarge + 3 * Theme.paddingLarge
            verticalAlignment: Text.AlignVCenter
            text: fullname
        }

        Switch {
            id: dialogOnlineStatus
            anchors.verticalCenter: dialogTitle.verticalCenter
            anchors.right: dialogTitle.left
            anchors.rightMargin: Theme.paddingMedium
            automaticCheck: false
            height: Theme.fontSizeLarge
            width: Theme.fontSizeLarge
            checked: isOnline
        }

        SilicaListView {
            id: messages
            anchors.fill: parent
            anchors.topMargin: dialogTitle.height
            anchors.bottomMargin: messageInput.height
            clip: true

            model: ListModel {}

            header: Button {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width / 3 * 2
                text: "Загрузить больше"
                onClicked: {
                    loadingMessagesIndicator.running = true
                    messagesOffset = messagesOffset + 50;
                    MessagesAPI.getHistory(isChat, dialogId, messagesOffset)
                }
            }

            delegate: MessageItem {}

            VerticalScrollDecorator {}
        }

        TextArea {
            id: messageInput
            width: parent.width
            anchors.bottom: parent.bottom
            placeholderText: "Сообщение:"
            label: "Сообщение"

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
                    loadingMessagesIndicator.running = true
                    MessagesAPI.getHistory(isChat, dialogId, messagesOffset)
                }
            }

            MenuItem {
                text: "Отметить прочитанным"
                onClicked: {
                    messages.model.clear()
                    messagesOffset = 0
                    loadingMessagesIndicator.running = true
                    MessagesAPI.markDialogAsRead(isChat, dialogId)
                }
            }
        }

        VerticalScrollDecorator {}
    }

    Component.onCompleted: {
        UsersAPI.getUserAvatar(StorageJS.readSettingsValue("user_id"))
        MessagesAPI.getHistory(isChat, dialogId, messagesOffset)
    }
}
