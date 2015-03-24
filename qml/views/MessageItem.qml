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

BackgroundItem {
    anchors.left: parent.left
    anchors.right: parent.right
    height: messageAvatar.height >= (messageText.height + datetimeText.height) ?
                messageAvatar.height + 2 * Theme.paddingMedium :
                messageText.height + datetimeText.height + 2 * Theme.paddingMedium
    highlighted: io === 0 & readState === 0

    Separator {
        anchors.top: parent.top
        width: parent.width
        color: Theme.secondaryHighlightColor
    }

    Row {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: Theme.paddingMedium
        anchors.leftMargin: Theme.paddingLarge
        anchors.rightMargin: Theme.paddingLarge
        spacing: Theme.paddingMedium
        layoutDirection: io === 0 ? Qt.LeftToRight : Qt.RightToLeft

        Image {
            id: messageAvatar
            height: Theme.itemSizeMedium - 2 * Theme.paddingSmall
            width: height
            source: io === 0 ? avatarSource : userAvatar
        }

        Column {
            width: parent.width - messageAvatar.width - Theme.paddingMedium

            Label {
                id: datetimeText
                width: parent.width - Theme.paddingMedium
                horizontalAlignment: io === 1 ? Text.AlignRight : Text.AlignLeft
                text: "24.03.2015 23:50"
                font.pixelSize: Theme.fontSizeTiny
                color: readState === 1 ? Theme.secondaryColor : Theme.secondaryHighlightColor
            }

            Label {
                id: messageText
                width: parent.width - Theme.paddingMedium
                horizontalAlignment: io === 1 ? Text.AlignRight : Text.AlignLeft
                text: message
                textFormat: Text.StyledText
                linkColor: readState === 1 ? Theme.secondaryColor : Theme.secondaryHighlightColor
                color: readState === 1 ? Theme.primaryColor : Theme.highlightColor
                wrapMode: Text.Wrap

                onLinkActivated: Qt.openUrlExternally(link)
            }
        }

    }
}
