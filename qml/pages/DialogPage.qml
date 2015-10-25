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
import "../js/types.js" as TypesJS
import "../js/api/messages.js" as MessagesAPI
import "../js/api/users.js" as UsersAPI

Page {
    id: dialogPage

    property string fullname
    property int dialogId
    property bool isChat
    property bool isOnline
    property string lastSeenTime
    property string avatarSource
    property string userAvatar
    property bool useSeparators: StorageJS.readSettingsValue("is_separated_messages") === 'true'

    property Item contextMenu

    property variant chatUsers: QtObject {}

    property string attachmentsList: ""

    function formNewDialogMessages() {
        console.log('formNewDialogMessages()')
        loadingMessagesIndicator.running = true
        var messagesArray = StorageJS.getLastMessagesForDialog(dialogId)
        for (var item in messagesArray) formMessageList(messagesArray[item])
        getLastHistoryFromServer(true)
        scrollMessagesToBottom(true)

        if (isChat) MessagesAPI.api_getChatUsers(dialogId)
        else UsersAPI.api_getUsersAvatarAndOnlineStatus(dialogId)
    }

    function saveUsers(users) {
        var usersDict = {}
        for (var index in users) usersDict[users[index].id] = users[index]
        chatUsers = usersDict
        pageContainer.pushAttached(Qt.resolvedUrl("../pages/ChatUsersPage.qml"),
                                   { "chatTitle": fullname, "users": users })
        MessagesAPI.api_getHistory(isChat, dialogId, 0)
    }

    function updateDialogInfo(userId, data) {
        if (dialogId === userId) {
            if (isChat) {
                if ("fullname" in data) fullname = data.fullname
            } else {
                if ("isOnline" in data) isOnline = data.isOnline
            }

            if ("avatarSource" in data) avatarSource = data.avatarSource
            if ("lastSeen" in data) lastSeenTime = data.lastSeen
        }
    }

    function sendMessage() {
        var text = encodeURIComponent(messageInput.text)
        MessagesAPI.api_sendMessage(isChat, dialogId, text, attachmentsList, false)
        messageInput.text = ""
        attachmentsList = ""
        markDialogAsRead()
    }

    function getUserAvatar(userId) {
        console.log("getUserAvatar(" + userId + ")");

        var avatar = "image://theme/icon-cover-people"

        if (isChat) {
            if (userId in chatUsers) avatar = chatUsers[userId].photo
        } else avatar = avatarSource

        console.log("avatar = " + avatar);
        return avatar
    }

    function formMessagesListFromServerData(messagesArray) {
        var toBottom = messages.model.count > 0 ?
                    messages.getMessageId(true) < messagesArray[0].mid :
                    false

        if (toBottom && messagesArray.length > 1 &&
                messagesArray[0].mid > messagesArray[messagesArray.length - 1].mid)
            messagesArray.reverse()

        for (var item in messagesArray) {
            var messageData = messagesArray[item]
            formMessageList(messageData, toBottom)
        }
        scrollMessagesToBottom(toBottom)
    }

    function formMessageList(messageData, insertToEnd) {
        var index = messages.lookupItem(messageData.mid)

        if (messageData.out === 0) {
            if (!messageData.avatarSource)
                messageData.avatarSource = getUserAvatar(messageData.fromId)
        } else messageData.userAvatar = userAvatar
        messageData.useSeparator = useSeparators
        if (index === -1) {
            index = (insertToEnd === true) ? messages.model.count : 0
            messages.model.insert(index, messageData)
        } else {
            messages.model.set(index, messageData)
        }
    }

    function addNewMessage(jsonMessage) {
        var fromId = jsonMessage.fromId ? jsonMessage.fromId : jsonMessage.user_id
        if (isChat)
            fromId = jsonMessage.chat_id

        if (dialogId === fromId) {
            var messageData = MessagesAPI.parseMessage(jsonMessage)
            formMessageList(messageData, true)
            scrollMessagesToBottom(true)
        }
    }

    function updateMessageInfo(userId, data) {
        if (dialogId === userId) {
            var msgIndex = messages.lookupItem(data.msgId)
            if (msgIndex !== -1) {
                if ("peerOut" in data) {
                    for (; 0 <= msgIndex; --msgIndex) {
                        var msg = messages.model.get(msgIndex)
                        if (msg.out === data.peerOut &&
                                            msg.readState !== data.readState) {
                            messages.model.setProperty(msgIndex,
                                                    "readState", data.readState)
                            StorageJS.updateMessage(msg.mid, {"is_read": data.readState})
                        }
                    }
                } else {
                    messages.model.setProperty(msgIndex,
                                                    "readState", data.readState)
                    StorageJS.updateMessage(data.msgId, {"is_read": data.readState})
                }
            }
        }
    }

    function scrollMessagesToBottom(toBottom) {
        if (toBottom) messages.positionViewAtEnd()
        else messages.positionViewAtIndex(MessagesAPI.HISTORY_COUNT - 2, ListView.Beginning)
    }

    function stopBusyIndicator() {
        loadingMessagesIndicator.running = false
    }

    function markDialogAsRead() {
        var unreadMessages = []
        for (var i = 0; i < messages.model.count; ++i) {
            var msg = messages.model.get(i)
            if (msg.readState === 0 && msg.out === 0) {
                unreadMessages.push(msg.mid)
                messages.model.setProperty(i, "readState", 1)
                StorageJS.updateMessage(msg.mid, {"is_read": 1})
            }
        }
        if (unreadMessages.length > 0)
            MessagesAPI.api_markDialogAsRead(unreadMessages.toString())
    }

    function getLastHistoryFromServer(fromLastMessage) {
        loadingMessagesIndicator.running = true
        var offset = 0
        var lastMsgId = null
        if (fromLastMessage === true) {
            lastMsgId = messages.getMessageId(true)
            if (lastMsgId > 0) offset = -MessagesAPI.HISTORY_COUNT
        }
        MessagesAPI.api_getHistory(isChat, dialogId, offset, lastMsgId)
    }

    BusyIndicator {
        id: loadingMessagesIndicator
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: true
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: dialogPage.height

        Label {
            id: dialogTitle
            anchors.top: parent.top
            anchors.right: parent.right
            font.pixelSize: Theme.fontSizeLarge
            color: Theme.highlightColor
            height: Theme.fontSizeLarge + 3 * Theme.paddingLarge
            width: parent.width - Theme.paddingLarge
            verticalAlignment: Text.AlignVCenter
            text: fullname
            elide: Text.ElideRight
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
                text: qsTr("Загрузить больше")
                onClicked: {
                    loadingMessagesIndicator.running = true
                    var topMsgId = messages.getMessageId(false)
                    MessagesAPI.api_getHistory(isChat, dialogId, 0, topMsgId)
                }
            }

            footer: Label {
                width: parent.width
                height: (isChat || isOnline) ? 0 : Theme.itemSizeSmall
                visible: !(isChat || isOnline)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("Был(a) в сети: %1").arg(lastSeenTime)
            }

            delegate: Item {
                id: messageItem

                property bool menuOpen: contextMenu != null && contextMenu.parent === messageItem

                height: menuOpen ? contextMenu.height + contentItem.height : contentItem.height
                width: parent.width

                MessageItem {
                    id: contentItem
                    width: parent.width

//                    onClicked: {
//                        dialogPage.pageContainer.push(Qt.resolvedUrl("MessagePage.qml"),
//                                                      { "fullname": dialogTitle.text,
//                                                        "isOnline": dialogOnlineStatus.isOnline,
//                                                        "messageText": message,
//                                                        "attachments": attachments })
//                    }
                    onPressAndHold: {
                        console.log(index)
                        if (!contextMenu)
                            contextMenu = contextMenuComponent.createObject(messages)
                        contextMenu.show(messageItem)
                    }
                }

                Component {
                    id: contextMenuComponent

                    ContextMenu {

                        property string message

                        MenuItem {
                            text: qsTr("Копировать текст")
                            onClicked: Clipboard.text = messages.model.get(index).message
                        }

                        onClosed: contextMenu = null
                    }
                }
            }

            VerticalScrollDecorator {}

            function lookupItem(itemId, fromEnd) {
                fromEnd = fromEnd === true

                for (var i = (fromEnd ? messages.model.count - 1 : 0);
                             (fromEnd ? i >= 0 : i < messages.model.count);
                             (fromEnd ? --i : ++i)) {
                    if (messages.model.get(i).mid === itemId) {
                        return i
                    }
                }
//                console.log("Message with id '" + itemId + "' does not exist")
                return -1
            }

            function getMessageId(isLast) {
                var msgId = -1
                if (messages.model.count > 0)
                    msgId = messages.model.get(isLast ? messages.model.count - 1 : 0).mid

                return msgId
            }
        }

        IconButton {
            id: attachmentsButton
            anchors.left: parent.left
            anchors.leftMargin: Theme.paddingLarge
            anchors.verticalCenter: messageInput.verticalCenter
            width: Theme.iconSizeSmallPlus
            height: Theme.iconSizeSmallPlus
            icon.width: Theme.iconSizeSmallPlus
            icon.height: Theme.iconSizeSmallPlus
            icon.fillMode: Image.PreserveAspectFit
            icon.source: "image://theme/icon-m-attach"
        }

        Label {
            id: attachmentsCounter
            anchors.verticalCenter: attachmentsButton.top
            anchors.left: attachmentsButton.left
            anchors.leftMargin: text === "10" ? 0 : Theme.paddingSmall
            anchors.verticalCenterOffset: Theme.paddingSmall
            font.bold: true
            font.pixelSize: Theme.fontSizeTiny
            color: Theme.highlightColor
            text: {
                var attachmentsCount = attachmentsList.split(',').length - 1
                return attachmentsCount > 0 ? attachmentsCount : ""
            }
        }

        TextArea {
            id: messageInput
            anchors.bottom: parent.bottom
            anchors.left: attachmentsButton.right
            anchors.right: parent.right
            placeholderText: qsTr("Сообщение:")
            label: qsTr("Сообщение")

            EnterKey.enabled: text.length > 0
            EnterKey.iconSource: "image://theme/icon-m-enter-accept"
            EnterKey.onClicked: sendMessage()
        }

        PushUpMenu {

            MenuItem {
                text: qsTr("Обновить")
                onClicked: {
                    markDialogAsRead()
                    getLastHistoryFromServer()
                }
            }

            MenuItem {
                text: qsTr("Прикрепить изображение")
                onClicked: {
                    var imagePicker = pageStack.push("Sailfish.Pickers.ImagePickerPage")
                    imagePicker.selectedContentChanged.connect(function () {
                        loadingMessagesIndicator.running = true
                        photos.attachImage(imagePicker.selectedContent, "MESSAGE", 0)
                    })
                }
            }
        }
    }

    Timer {
        interval: 0
        running: Qt.application.active
        repeat: false
        triggeredOnStart: true

        onTriggered: {
            if (messages.count > 0) {
                getLastHistoryFromServer(true)
                scrollMessagesToBottom(true)
            }
        }
    }

    Connections {
        target: photos
        onImageUploaded: {
            attachmentsList += imageName + ","
            loadingMessagesIndicator.running = false
        }
    }

    onStatusChanged:
        if (status === PageStatus.Inactive) markDialogAsRead()
        else if (status === PageStatus.Active) formNewDialogMessages()

    onChatUsersChanged: {
        console.log("onChatUsersChanged: ...")
        for (var i = 0; i < messages.count; ++i) {
            var msg = messages.model.get(i)
            var avatar = getUserAvatar(msg.fromId)
            if (avatar !== msg.avatarSource) messages.model.setProperty(i, "avatarSource", avatar)
        }
    }

    onAvatarSourceChanged: {
        if (!isChat) {
            for (var i = 0; i < messages.count; ++i) {
                var msg = messages.model.get(i)
                if (avatarSource !== msg.avatarSource && msg.out === 0)
                    messages.model.setProperty(i, "avatarSource", avatarSource)
            }
        }

    }

    Component.onCompleted: {
        MessagesAPI.signaller.endLoading.connect(stopBusyIndicator)
        MessagesAPI.signaller.gotDialogInfo.connect(updateDialogInfo)
        MessagesAPI.signaller.gotChatUsers.connect(saveUsers)
        MessagesAPI.signaller.gotHistory.connect(formMessagesListFromServerData)
        MessagesAPI.signaller.gotMessageInfo.connect(updateMessageInfo)
        MessagesAPI.signaller.gotNewMessage.connect(addNewMessage)
        UsersAPI.signaller.endLoading.connect(stopBusyIndicator)
        UsersAPI.signaller.gotDialogInfo.connect(updateDialogInfo)
    }

    Component.onDestruction: {
        MessagesAPI.signaller.endLoading.disconnect(stopBusyIndicator)
        MessagesAPI.signaller.gotDialogInfo.disconnect(updateDialogInfo)
        MessagesAPI.signaller.gotChatUsers.disconnect(saveUsers)
        MessagesAPI.signaller.gotHistory.disconnect(formMessagesListFromServerData)
        MessagesAPI.signaller.gotMessageInfo.disconnect(updateMessageInfo)
        MessagesAPI.signaller.gotNewMessage.disconnect(addNewMessage)
        UsersAPI.signaller.endLoading.disconnect(stopBusyIndicator)
        UsersAPI.signaller.gotDialogInfo.disconnect(updateDialogInfo)
    }
}
