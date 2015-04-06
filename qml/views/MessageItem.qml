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
    /*
     out
     readState
    */

    function calculateMessageItemHeight() {
        var textHeight = datetimeText.height + messageText.height /*+ attachmentsText.height*/
        return Math.max(messageAvatar.height, textHeight) + 2 * Theme.paddingMedium
    }

    anchors.left: parent.left
    anchors.right: parent.right
    height: calculateMessageItemHeight()
    highlighted: out === 0 & readState === 0

//    Separator {
//        anchors.top: parent.top
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.leftMargin: Theme.paddingMedium
//        anchors.rightMargin: Theme.paddingMedium
//        color: Theme.secondaryHighlightColor
//    }

    Row {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: Theme.paddingMedium
        anchors.leftMargin: Theme.paddingLarge
        anchors.rightMargin: Theme.paddingLarge
        spacing: Theme.paddingMedium
        layoutDirection: out === 0 ? Qt.LeftToRight : Qt.RightToLeft

        Image {
            id: messageAvatar
            height: Theme.itemSizeSmall - 2 * Theme.paddingSmall
            width: height
            source: out === 0 ? avatarSource : userAvatar
        }

        Column {

            Label {
                id: messageText
                width: parent.parent.width - Theme.paddingMedium - messageAvatar.width
                horizontalAlignment: out === 1 ? Text.AlignRight : Text.AlignLeft
                text: message
                textFormat: Text.StyledText
                linkColor: readState === 1 ? Theme.secondaryColor : Theme.secondaryHighlightColor
                color: readState === 1 ? Theme.primaryColor : Theme.highlightColor
                wrapMode: Text.Wrap

                onLinkActivated: Qt.openUrlExternally(link)
            }

//            Label {
//                id: attachmentsText
//                width: parent.parent.width - Theme.paddingMedium - messageAvatar.width
//                horizontalAlignment: out === 1 ? Text.AlignRight : Text.AlignLeft
//                text: attachments
//                font.pixelSize: Theme.fontSizeSmall
//                textFormat: Text.StyledText
//                linkColor: readState === 1 ? Theme.secondaryColor : Theme.secondaryHighlightColor
//            }

            Label {
                id: datetimeText
                width: parent.parent.width - Theme.paddingMedium - messageAvatar.width
                horizontalAlignment: out === 1 ? Text.AlignRight : Text.AlignLeft
                text: datetime
                font.pixelSize: Theme.fontSizeTiny
                color: readState === 1 ? Theme.secondaryColor : Theme.secondaryHighlightColor
            }
        }

    }
}
