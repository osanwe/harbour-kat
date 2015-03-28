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

Page {
    /*
      Fields:
          fullname
          isOnline
          messageText
    */
    id: messagePage

    property bool isOnline
    property string fullname
    property string messageText

//    BusyIndicator {
//        id: loadingMessageIndicator
//        anchors.centerIn: parent
//        size: BusyIndicatorSize.Large
//        running: true
//    }

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

        Label {
            id: messageContent
            anchors.top: dialogTitle.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: Theme.paddingLarge
            anchors.rightMargin: Theme.paddingLarge
            textFormat: Text.StyledText
            linkColor: Theme.secondaryColor
            color: Theme.primaryColor
            wrapMode: Text.Wrap
            text: messageText
        }

//        SilicaListView {
//            id: messages
//            anchors.fill: parent
//            anchors.topMargin: dialogTitle.height
//            anchors.bottomMargin: messageInput.height
//            clip: true

//            model: ListModel {}

//            delegate: MessageItem {}

//            VerticalScrollDecorator {}
//        }
    }

    Component.onCompleted: {
        UsersAPI.getUserAvatar(StorageJS.readSettingsValue("user_id"))
        MessagesAPI.getHistory(isChat, dialogId, messagesOffset)
    }
}
