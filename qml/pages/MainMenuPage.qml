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
import "../js/api/users.js" as UsersAPI

Page {

    property string userAvatarUrl: "image://theme/icon-l-people"
    property string userFullName: "Имя Фамилия"

    SilicaListView {
        id: mainMenu
        anchors.fill: parent

        header: BackgroundItem {
            width: parent.width
            height: Theme.itemSizeMedium

            Image {
                id: userAvatar
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingLarge
                anchors.verticalCenter: parent.verticalCenter
                width: Theme.itemSizeMedium - 2 * Theme.paddingMedium
                height: Theme.itemSizeMedium - 2 * Theme.paddingMedium
                source: userAvatarUrl

                Connections {
                    target: fileDownloader
                    onDownloaded: {
                        userAvatarUrl = "/home/nemo/.cache/harbour-kat/" + StorageJS.readUserAvatar()
                        userAvatar.source = userAvatarUrl
                    }
                }
            }

            Label {
                id: userName
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: Theme.fontSizeLarge
                height: Theme.itemSizeMedium
                verticalAlignment: Text.AlignVCenter
                color: Theme.highlightColor
                text: userFullName
            }
        }

        model: ListModel {
            ListElement {
                icon: "image://theme/icon-l-message"
                name: "Новости"
                counter: ""
            }
            ListElement {
                icon: "image://theme/icon-l-redirect"
                name: "Ответы"
                counter: "0"
            }
            ListElement {
                icon: "image://theme/icon-l-email"
                name: "Сообщения"
                counter: "0"
            }
            ListElement {
                icon: "image://theme/icon-l-people"
                name: "Друзья"
                counter: "0"
            }
            ListElement {
                icon: "image://theme/icon-l-people"
                name: "Группы"
                counter: "0"
            }
            ListElement {
                icon: "image://theme/icon-l-image"
                name: "Фотографии"
                counter: "0"
            }
            ListElement {
                icon: "image://theme/icon-l-video"
                name: "Видеозаписи"
                counter: "0"
            }
            ListElement {
                icon: "image://theme/icon-l-music"
                name: "Аудиозаписи"
                counter: ""
            }
            ListElement {
                icon: "image://theme/icon-l-favorite"
                name: "Закладки"
                counter: ""
            }
            ListElement {
                icon: "image://theme/icon-l-document"
                name: "Документы"
                counter: ""
            }
            ListElement {
                icon: "image://theme/icon-cover-search"
                name: "Поиск"
                counter: ""
            }
        }

        delegate: BackgroundItem {
            id: menuItem
            height: Theme.itemSizeSmall

            Item {
                anchors.fill: parent
                anchors.rightMargin: Theme.paddingLarge
                anchors.leftMargin: Theme.paddingLarge

                Image {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    width: Theme.iconSizeMedium
                    height: Theme.iconSizeMedium
                    source: icon
                }

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color: menuItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    text: name
                }

                Label {
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                    color: menuItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    text: counter
                }
            }

            onClicked: {
                switch (index) {
                case 0:
                    break

                case 1:
                    break

                case 2:
                    pageStack.push(Qt.resolvedUrl("MessagesPage.qml"))
                    break;

                case 3:
                    break

                case 4:
                    break

                case 5:
                    break

                case 6:
                    break

                case 7:
                    break

                case 8:
                    break

                case 9:
                    break

                case 10:
                    break
                }
            }
        }
    }

    onStatusChanged: if (status === PageStatus.Active) getUpdates()
    Component.onCompleted: StorageJS.initDatabase()


    function getUpdates() {
        if (!StorageJS.readSettingsValue("user_id")) {
            pageStack.push(Qt.resolvedUrl("LoginPage.qml"))
        } else {
            // From database
            var fullUserName = StorageJS.readFullUserName()
            var avatarFileName = StorageJS.readUserAvatar()
            updateUserInfo(fullUserName, "/home/nemo/.cache/harbour-kat/" + avatarFileName)
            // Update now if need
            UsersAPI.api_getUserNameAndAvatar(StorageJS.readSettingsValue("user_id"))
        }
    }

    function updateUserInfo(name, avatarUrl) {
        console.log("updateUserInfo()")
        userFullName = name
        userAvatarUrl = avatarUrl
    }
}
