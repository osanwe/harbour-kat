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

Page {

    property string textBody
    property string datetime
    property string postAuthor
    property variant attachmentsData

    SilicaFlickable {
        anchors.fill: parent
        anchors.bottomMargin: Theme.paddingLarge
        contentHeight: newsAuthor.height + newsContent.height

        Label {
            id: newsAuthor
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: Theme.paddingLarge
            font.pixelSize: Theme.fontSizeLarge
            color: Theme.highlightColor
            width: parent.width
            height: Theme.fontSizeLarge + 3 * Theme.paddingLarge
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            text: postAuthor
        }

        ContentItem {
            id: newsContent
            anchors.top: newsAuthor.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: Theme.paddingLarge
            anchors.rightMargin: Theme.paddingLarge
            attachments: attachmentsData
            content: textBody
            dateTime: datetime
            isNews: false
        }
    }
}
