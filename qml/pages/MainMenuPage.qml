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
import "../js/storage.js" as StorageJS
import "../js/api/messages.js" as MessagesAPI
import "../js/api/users.js" as UsersAPI

Page {
    id: mainMenuPage

    property string userAvatarUrl: "image://theme/icon-l-people"
    property string userFullName: qsTr("Имя Фамилия")

    property var model: [
        { name: qsTr("Новости"), counter: "" },
//        { name: "Ответы", counter: "0" },
        { name: qsTr("Сообщения"), counter: "" },
//        { name: "Друзья", counter: "0" },
//        { name: "Группы", counter: "0" },
//        { name: "Фотографии", counter: "0" },
//        { name: "Видеозаписи", counter: "0" },
//        { name: "Аудиозаписи", counter: "" },
//        { name: "Закладки", counter: "" },
//        { name: "Документы", counter: "" },
//        { name: "Поиск", counter: "" },
        { name: qsTr("Настройки"), counter: "" },
        { name: qsTr("О программе"), counter: "" }
    ]

    function doStartUpdate() {
        if (StorageJS.readSettingsValue("user_id")) {
            var fullUserName = StorageJS.readFullUserName()
            var avatarFileName = StorageJS.readUserAvatar()
            updateUserNameAndAvatar(fullUserName, cachePath + avatarFileName)
            // TODO Calculating unread messages counter with cached data

            doForceUpdate()
        }
    }

    function doForceUpdate() {
        UsersAPI.api_getUserNameAndAvatar(StorageJS.readSettingsValue("user_id"))
        MessagesAPI.api_getUnreadMessagesCounter(false)
    }

    function updateUserNameAndAvatar(name, avatarUrl) {
        console.log("updateUserInfo()")
        userFullName = name
        userAvatarUrl = avatarUrl
    }
    SilicaListView {
        anchors.fill: parent

        function updateUnreadMessagesCounter(counter) {
    //        mainMenu.model.setProperty(1, "counter", counter ? counter : "")
        }

        model: mainMenuPage.model

        header: PageHeader {
            title: userFullName
        }

        delegate: BackgroundItem {
            id: menuItem
            height: Theme.itemSizeSmall

            property var item: model.modelData ? model.modelData : model

            Item {
                anchors.fill: parent
                anchors.rightMargin: Theme.paddingLarge
                anchors.leftMargin: Theme.paddingLarge

                Label {
                    id: menuItemText
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    color: menuItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    maximumLineCount: 1
                    truncationMode: TruncationMode.Fade
                    text: item.name
                }

                Rectangle {
                    anchors.left: menuItemText.right
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.verticalCenter: parent.verticalCenter
                    width: menuItemCounter.width < menuItemCounter.height ? menuItemCounter.height : menuItemCounter.width + 2 * Theme.paddingSmall
                    height: menuItemCounter.height
                    radius: 10
                    color: Theme.highlightColor
                    visible: item.counter !== ''

                    Label {
                        id: menuItemCounter
                        anchors.centerIn: parent
                        font.bold: true
                        color: menuItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                        text: item.counter
                    }
                }
            }

            onClicked:
                switch (index) {
                case 0:
                    pageContainer.replaceAbove(null, Qt.resolvedUrl("NewsfeedPage.qml"))
                    pageContainer.pushAttached(Qt.resolvedUrl("MainMenuPage.qml"))
                    break

                case 1:
                    pageContainer.replaceAbove(null, Qt.resolvedUrl("DialogsListPage.qml"))
                    pageContainer.pushAttached(Qt.resolvedUrl("MainMenuPage.qml"))
                    break

                case 2:
                    pageContainer.push(Qt.resolvedUrl("SettingsPage.qml"))
                    break;

                case 3:
    //                break

    //            case 4:
    //                break

    //            case 5:
    //                break

    //            case 6:
    //                break

    //            case 7:
    //                break

    //            case 8:
    //                break

    //            case 9:
    //                break

    //            case 10:
    //                break

    //            case 11:
//                    break;

//                case 12:
//                    break;
                    pageContainer.push(Qt.resolvedUrl("AboutPage.qml"))
                    break
                }
        }

        VerticalScrollDecorator {}
    }

    Component.onCompleted: {
        UsersAPI.signaller.gotUserNameAndAvatar.connect(updateUserNameAndAvatar)

        doStartUpdate()
    }

    Component.onDestruction: {
        UsersAPI.signaller.gotUserNameAndAvatar.disconnect(updateUserNameAndAvatar)
    }
}
