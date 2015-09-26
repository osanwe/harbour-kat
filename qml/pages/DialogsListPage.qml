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

    property int chatsCounter: 0
    property int dialogsOffset: 0
    property var dialogsData: []
    property var usersAvatars: []

    function formNewDialogsList() {
        console.log('formNewDialogsList()')
        var lastDialogs = StorageJS.getLastDialogs()
        for (var item in lastDialogs) messagesList.model.append(lastDialogs[item])
        updateDialogs()
    }

    function updateDialogs() {
        console.log('updateDialogs()')
        if (StorageJS.readSettingsValue("user_id")) {
            dialogsOffset = 0
            chatsCounter = 0
            dialogsData = []
            usersAvatars = []
            loadingIndicator.running = true
            messagesList.footerItem.visible = false
            MessagesAPI.api_getDialogsList(dialogsOffset)
        }
    }

    function formDialogsList(io, title, message, dialogId, readState, isChat) {
        console.log(readState)
        message = message.replace(/<br>/g, " ")
        dialogsData[dialogsData.length] = { isDialog:     true,
                                            out:          io,
                                            avatarSource: "image://theme/icon-cover-message",
                                            nameOrTitle:  title,
                                            previewText:  message,
                                            itemId:       dialogId,
                                            readState:    readState,
                                            isOnline:     false,
                                            isChat:       isChat }
    }

    function updateDialogInfo(index, avatarURL, fullname, online, lastSeen) {
        while (dialogsData[parseInt(index, 10) + chatsCounter + dialogsOffset].isChat)
            chatsCounter += 1
        var idx = parseInt(index, 10) + chatsCounter + dialogsOffset
        var dialog = dialogsData[idx]
        usersAvatars[usersAvatars.length] = avatarURL
        dialog.avatarSource = avatarURL
        dialog.nameOrTitle = fullname
        dialog.isOnline = online
        dialogsData[idx] = dialog
    }

    function stopBusyIndicator() {
        messagesList.model.clear()
        for (var item in dialogsData) messagesList.model.append(dialogsData[item])
        messagesList.footerItem.visible = true
        loadingIndicator.running = false
        if (usersAvatars.length > 0) fileDownloader.startDownload(usersAvatars[0], 0)
    }

    Connections {
        target: fileDownloader
        onDownloaded: {
            usersAvatars = usersAvatars.slice(1)
            if (usersAvatars.length > 0) fileDownloader.startDownload(usersAvatars[0], 0)
        }
    }

    BusyIndicator {
        id: loadingIndicator
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: false // true
    }

    SilicaListView {
        id: messagesList
        anchors.fill: parent
        anchors.bottomMargin: Theme.paddingMedium

        PullDownMenu {

            MenuItem {
                id: newMessageItem
                text: qsTr("Новое сообщение")
                onClicked: pageContainer.push(Qt.resolvedUrl("NewMessagePage.qml"))
            }

            MenuItem {
                id: mainMenuItem
                text: qsTr("Обновить")
                onClicked: updateDialogs()
            }
        }

        header: PageHeader {
            title: qsTr("Сообщения")
        }

        model: ListModel {}

        delegate: UserItem {

            onClicked: {
                pageContainer.push(Qt.resolvedUrl("../pages/DialogPage.qml"),
                                          { "fullname":     nameOrTitle,
                                            "dialogId":     itemId,
                                            "isChat":       isChat,
                                            "userAvatar":   cachePath + StorageJS.readUserAvatar() })
            }
        }

        footer: Button {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width / 3 * 2
            text: qsTr("Загрузить больше")

            onClicked: {
                loadingIndicator.running = true
                dialogsOffset = dialogsOffset + 20
                chatsCounter = 0
                MessagesAPI.api_getDialogsList(dialogsOffset)
            }
        }

        VerticalScrollDecorator {}
    }

    Timer {
        interval: 0
        running: Qt.application.active

        onTriggered: if (visible)
                         if (messagesList.model.count === 0) formNewDialogsList()
                         else updateDialogs()
    }
}
