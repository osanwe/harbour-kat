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

SilicaListView {
    anchors.fill: parent

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
                width: Theme.iconSizeSmall
                height: Theme.iconSizeSmall
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
    }

    VerticalScrollDecorator {}
}
