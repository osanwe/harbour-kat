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
    property string lastSeenTime
    property string avatarSource
    property string userAvatar

    property Item contextMenu

    property int messagesOffset: 0

    property variant chatUsers

    property string attachmentsList: ""

    function updateDialogInfo(index, avatarURL, name, online, lastSeen) {
        avatarSource = avatarURL
        fullname = name
        isOnline = online
        lastSeenTime = lastSeen
        MessagesAPI.api_getHistory(isChat, dialogId, messagesOffset)
    }

    function sendMessage() {
        messages.model.clear()
        messagesOffset = 0
        MessagesAPI.api_sendMessage(isChat, dialogId, encodeURIComponent(messageInput.text), attachmentsList, false)
        messageInput.text = ""
        attachmentsList = ""
    }

    function formMessageList(messageData) {
        var attachmentsData = messageData.slice(6)
        console.log(attachmentsData)
        if (isChat) {
            for (var index in chatUsers) {
                if (chatUsers[index].id === messageData[1]) {
                    avatarSource = chatUsers[index].photo
                }
            }

            messages.model.insert(0, { mid:             messageData[0],
                                       readState:       messageData[2],
                                       out:             messageData[3],
                                       message:         messageData[4],
                                       datetime:        messageData[5],
                                       avatarSource:    avatarSource,
                                       userAvatar:      userAvatar,
                                       attachmentsData: attachmentsData,
                                       isNewsContent:   false })
        } else {
            messages.model.insert(0, { mid:             messageData[0],
                                       readState:       messageData[2],
                                       out:             messageData[3],
                                       message:         messageData[4],
                                       datetime:        messageData[5],
                                       avatarSource:    avatarSource,
                                       userAvatar:      userAvatar,
                                       attachmentsData: attachmentsData,
                                       isNewsContent:   false })
        }
    }

    function scrollMessagesToBottom() {
        if (messagesOffset === 0) {
            messages.positionViewAtEnd()
        } else {
            messages.positionViewAtIndex(49, ListView.Beginning)
        }
    }

    function saveUsers(users) {
        chatUsers = users
        pageContainer.pushAttached(Qt.resolvedUrl("../pages/ChatUsersPage.qml"),
                                   { "chatTitle": fullname, "users": users })
        MessagesAPI.api_getHistory(isChat, dialogId, messagesOffset)
    }

    function stopLoadingMessagesIndicator() {
        loadingMessagesIndicator.running = false
    }

    function getUnreadMessagesFromModel() {
        var messagesIdsList = ""
        var index = 0
        while (index < messages.model.count) {
            console.log(index)
            if (messages.model.get(index).readState === 0) {
                console.log(messages.model.get(index).mid)
                messagesIdsList += "," + messages.model.get(index).mid
            }
            index += 1
        }
        console.log(messagesIdsList)
        return messagesIdsList.length !== 0 ? messagesIdsList.substring(1) : messagesIdsList
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
                text: qsTr("Загрузить больше")
                onClicked: {
                    loadingMessagesIndicator.running = true
                    messagesOffset = messagesOffset + 50;
                    MessagesAPI.api_getHistory(isChat, dialogId, messagesOffset)
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
                    messages.model.clear()
                    messagesOffset = 0
                    loadingMessagesIndicator.running = true
                    MessagesAPI.api_getHistory(isChat, dialogId, messagesOffset)
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

    Connections {
        target: photos
        onImageUploaded: {
            attachmentsList += imageName + ","
            loadingMessagesIndicator.running = false
        }
    }

    onStatusChanged:
        if (status === PageStatus.Inactive) {
            var unreadMessagesIds = getUnreadMessagesFromModel()
            if (unreadMessagesIds.length > 0)
                MessagesAPI.api_markDialogAsRead(isChat, dialogId, unreadMessagesIds)
        }
    Component.onCompleted:
        if (isChat) {
            MessagesAPI.api_getChatUsers(dialogId)
        } else {
            UsersAPI.getUsersAvatarAndOnlineStatus(dialogId)
        }
}
