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
  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    width: parent.width
    height: Theme.itemSizeMedium
    highlighted: io === 0 && readState === 0

    function loadDialogPage() {
        console.log("dialog id = " + dialogId)
        pageStack.push(Qt.resolvedUrl("../pages/DialogPage.qml"),
                       { "fullname": name.text, "dialogId": dialogId, "isChat": isChat })
    }

    Image {
        id: avatar
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: Theme.paddingSmall
        anchors.bottomMargin: Theme.paddingSmall
        anchors.leftMargin: Theme.paddingLarge
        width: height
        source: avatarSource
    }

    Row {
        anchors.top: avatar.top
        anchors.left: avatar.right
        anchors.leftMargin: Theme.paddingMedium
        anchors.right: parent.right
        anchors.rightMargin: Theme.paddingLarge
        spacing: Theme.paddingMedium

        Switch {
            id: isUserOnline
            height: name.height
            width: height
            automaticCheck: false
            checked: isOnline
        }

        Label {
            id: name
            color: { readState === 0 && io === 0 ? Theme.highlightColor : Theme.primaryColor }
            text: nameOrTitle
            truncationMode: TruncationMode.Fade
            font.bold: true
        }
    }

    Label {
        id: messagePreview
        anchors.bottom: avatar.bottom
        anchors.left: avatar.right
        anchors.leftMargin: Theme.paddingMedium
        anchors.right: parent.right
        anchors.rightMargin: Theme.paddingLarge
        color: { readState === 1 ? Theme.secondaryColor : Theme.secondaryHighlightColor }
        text: lastMessage
        truncationMode: TruncationMode.Fade
    }

    onClicked: loadDialogPage()
}
