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
import "../js/signals.js" as SignalsJS
import "../js/storage.js" as StorageJS
import "../js/api/messages.js" as MessagesAPI
import "../js/api/users.js" as UsersAPI
import "../js/types.js" as TypesJS

Page {

    property int dialogsOffset: 0
    property var dialogsData: []
    property var usersAvatars: []

    /**
     * The function searches the index of dialog by id.
     * @param itemId - dialog id for searching
     * @return The index of dialog or -1 if it was not found.
     */
    function lookupItem(itemId) {
        console.log('lookupItem(' + itemId + ')');
        if (itemId < 0) return -1;
        for (var i = 0; i < dialogsData.length; ++i) {
            if (dialogsData[i].itemId === itemId) return i;
        }
        return -1;
    }

    /**
     * The method starts dialogs update process.
     */
    function updateDialogs() {
        console.log('updateDialogs()');
        if (StorageJS.readSettingsValue("user_id")) {
            dialogsOffset = 0;
            dialogsData = [];
            usersAvatars = [];
            loadingIndicator.running = true;
            messagesList.footerItem.visible = false;
            MessagesAPI.api_getDialogsList(dialogsOffset);
        }
    }

    /**
     * The function forms dialogs list after reading information from database.
     */
    function formDialogsListFromDb() {
        console.log('formDialogsListFromDb()');
        var lastDialogs = StorageJS.getLastDialogs();
        for (var item in lastDialogs) messagesList.model.append(lastDialogs[item]);
        updateDialogs();
    }

    /**
     * The function forms dialogs list after getting information from server.
     * @param listItemData - the information about dialog
     * @param isFirst - if true, add the element to start of the array
     */
    function formDialogsList(listItemData, isFirst) {
        console.log('formDialogsList(' + listItemData + ')');
        if (listItemData) {
            var newData = { isDialog:     true,
                            out:          listItemData[0],
                            avatarSource: "image://theme/icon-cover-message",
                            nameOrTitle:  listItemData[1],
                            previewText:  listItemData[2],
                            itemId:       listItemData[3],
                            readState:    listItemData[4],
                            isOnline:     false,
                            isChat:       listItemData[5] };
            if (isFirst) dialogsData.unshift(newData);
            else dialogsData.push(newData);
        }
    }

    /**
     * The function updates dialogs list after getting new information from long poll server.
     * @param jsonMessage - the information about new message in json format
     */
    function updateDialogsList(jsonMessage) {
        console.log('updateDialogsList(' + JSON.stringify(jsonMessage) +')');
        var itemData = MessagesAPI.parseDialogListItem(jsonMessage);

        var uid = jsonMessage.from_id;
        var isChat = itemData[5];
        var dialogIndex = lookupItem(itemData[3]);

        if (dialogIndex !== -1) {
            var data = { out:         itemData[0],
                         previewText: itemData[2],
                         readState:   itemData[4] };
            if (isChat) data["nameOrTitle"] = itemData[1];

            updateDialogInfo(itemData[3], data);

            data = dialogsData.splice(dialogIndex, 1)[0];
            dialogsData.unshift(data);

            flushDialogsData();
        } else {
            formDialogsList(itemData, true);
            if (isChat) MessagesAPI.api_getChat(itemData[3]);
            else UsersAPI.api_getUsersAvatarAndOnlineStatus(uid);
        }
    }

    /**
     * The function update the information about certain dialog.
     * @param dialogId - dialog id for updating
     * @param data - new information for updating
     */
    function updateDialogInfo(dialogId, data) {
        console.log("updateDialogInfo(" + dialogId + ", " + JSON.stringify(data) + ")");

        var idx = lookupItem(dialogId);

        if (idx !== -1) {
            var infoKeys = Object.keys(data);
            for (var i in infoKeys) {
                var key = infoKeys[i];
                if (key in dialogsData[idx]) dialogsData[idx][key] = data[key];
                if (key === 'avatarSource') usersAvatars.push(data[key]);
            }
        }
    }

    /**
     * The function shows the saved dialogs data.
     */
    function flushDialogsData() {
        console.log('flushDialogsData()');
        messagesList.model.clear();
        for (var item in dialogsData) messagesList.model.append(dialogsData[item]);
        messagesList.footerItem.visible = true;
    }

    /**
     * The function finished dialogs updating process.
     */
    function stopBusyIndicator() {
        console.log('stopBusyIndicator()');
        flushDialogsData();
        loadingIndicator.running = false;
        if (usersAvatars.length > 0 && !fileDownloader.isWorkNow()) {
            fileDownloader.startDownload(usersAvatars[0], 0);
        }
    }

    /**
     * The function starts dialogs auto updating with long poll server.
     */
    function startAutoUpdate() {
        if (!TypesJS.MessageUpdateMode.isManual() && !TypesJS.LongPollWorker.isActive()) {
            MessagesAPI.api_startLongPoll(TypesJS.LongPollMode.ATTACH);
        }
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
                console.log("dialogId = " + itemId)
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
                MessagesAPI.api_getDialogsList(dialogsOffset)
            }
        }

        VerticalScrollDecorator {}
    }

    Timer {
        interval: 60000
        running: Qt.application.active
        repeat: false
        triggeredOnStart: true

        property bool isFirstIteration: true

        onRunningChanged: {
            if (running) {
                isFirstIteration = true
                repeat = !TypesJS.MessageUpdateMode.isManual()
            }
        }

        onTriggered: {
            if (visible && isFirstIteration) {
                if (messagesList.model.count === 0) formDialogsListFromDb()
                else updateDialogs()

                isFirstIteration = false
            }

            startAutoUpdate()
        }
    }

    onStatusChanged: {
        if (status === PageStatus.Active) startAutoUpdate()
    }

    Component.onCompleted: {
        SignalsJS.signaller.endLoading.connect(stopBusyIndicator)
        SignalsJS.signaller.gotMessageInfo.connect(updateDialogInfo)
        SignalsJS.signaller.gotNewMessage.connect(updateDialogsList)
        SignalsJS.signaller.gotDialogInfo.connect(updateDialogInfo)
        SignalsJS.signaller.gotDialogs.connect(formDialogsList)
    }

    Component.onDestruction: {
        SignalsJS.signaller.endLoading.disconnect(stopBusyIndicator)
        SignalsJS.signaller.gotMessageInfo.disconnect(updateDialogInfo)
        SignalsJS.signaller.gotNewMessage.disconnect(updateDialogsList)
        SignalsJS.signaller.gotDialogInfo.disconnect(updateDialogInfo)
        SignalsJS.signaller.gotDialogs.disconnect(formDialogsList)
    }
}
