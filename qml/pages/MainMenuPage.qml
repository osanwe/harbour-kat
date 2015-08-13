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

    property string userAvatarUrl: "image://theme/icon-l-people"
    property string userFullName: "Имя Фамилия"

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

        model: ListModel {

            ListElement {
                icon: "image://theme/icon-l-message"
                name: "Новости"
                counter: ""
            }

    //        ListElement {
    //            icon: "image://theme/icon-l-redirect"
    //            name: "Ответы"
    //            counter: "0"
    //        }

            ListElement {
                icon: "image://theme/icon-l-email"
                name: "Сообщения"
                counter: ""
            }

    //        ListElement {
    //            icon: "image://theme/icon-l-people"
    //            name: "Друзья"
    //            counter: "0"
    //        }

    //        ListElement {
    //            icon: "image://theme/icon-l-people"
    //            name: "Группы"
    //            counter: "0"
    //        }

    //        ListElement {
    //            icon: "image://theme/icon-l-image"
    //            name: "Фотографии"
    //            counter: "0"
    //        }

    //        ListElement {
    //            icon: "image://theme/icon-l-video"
    //            name: "Видеозаписи"
    //            counter: "0"
    //        }

    //        ListElement {
    //            icon: "image://theme/icon-l-music"
    //            name: "Аудиозаписи"
    //            counter: ""
    //        }

    //        ListElement {
    //            icon: "image://theme/icon-l-favorite"
    //            name: "Закладки"
    //            counter: ""
    //        }

    //        ListElement {
    //            icon: "image://theme/icon-l-document"
    //            name: "Документы"
    //            counter: ""
    //        }

    //        ListElement {
    //            icon: "image://theme/icon-cover-search"
    //            name: "Поиск"
    //            counter: ""
    //        }

            ListElement {
                icon: ""
                name: "Настройки"
                counter: ""
            }

            ListElement {
                icon: ""
                name: "О программе"
                counter: ""
            }
        }

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
                        userAvatarUrl = cachePath + StorageJS.readUserAvatar()
                        userAvatar.source = userAvatarUrl
                    }
                }
            }

            Label {
                id: userName
                anchors.left: userAvatar.right
                anchors.right: parent.right
                anchors.leftMargin: Theme.paddingMedium
                height: Theme.itemSizeMedium
                verticalAlignment: Text.AlignVCenter
                color: Theme.highlightColor
                wrapMode: Text.WordWrap
                text: userFullName
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
                    id: menuItemIcon
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    width: Theme.iconSizeMedium
                    height: Theme.iconSizeMedium
                    source: icon
                }

                Label {
                    anchors.left: menuItemIcon.right
                    anchors.right: menuItemCounter.left
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.rightMargin: menuItemCounter.text.length > 0 ? Theme.paddingMedium : 0
                    anchors.verticalCenter: parent.verticalCenter
                    color: menuItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    maximumLineCount: 1
                    truncationMode: TruncationMode.Fade
                    text: name
                }

                Label {
                    id: menuItemCounter
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                    color: menuItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    text: counter
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

    Component.onCompleted: doStartUpdate()
}
