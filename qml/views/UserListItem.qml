/*
  Copyright (C) 2016 Petr Vytovtov
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

BackgroundItem {
    id: userListItem
    anchors.left: parent.left
    anchors.right: parent.right
    height: Theme.itemSizeMedium

    property var isUser
    property alias avatarSource: avatar.source
    property alias onlineStatus: online.checked
    property alias titleText: title.text
    property alias bodyText: body.text

    Row {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin
        height: parent.height
        spacing: Theme.paddingMedium

        Image {
            id: avatar
            anchors.verticalCenter: parent.verticalCenter
            width: Theme.iconSizeMedium
            height: Theme.iconSizeMedium
            fillMode: Image.PreserveAspectFit
        }

        Column {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - avatar.width - Theme.paddingMedium

            Row {
                width: parent.width
                spacing: Theme.paddingMedium

                Switch {
                    id: online
                    width: title.height
                    height: title.height
                    automaticCheck: false
                    visible: isUser
                }

                Label {
                    id: title
                    width: parent.width - online.width - Theme.paddingMedium
                    color: userListItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    truncationMode: TruncationMode.Fade
                    font.bold: true
                }
            }

            Label {
                id: body
                width: parent.width
                color: userListItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                truncationMode: TruncationMode.Fade
            }
        }
    }
}

