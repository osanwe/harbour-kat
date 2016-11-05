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

ListItem {
    id: wallItem
    width: parent.width
    contentHeight: content.height + 2 * Theme.paddingLarge

    Item {
        id: content
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin
        height: childrenRect.height

        Image {
            id: avatar
            anchors.left: parent.left
            anchors.top: parent.top
            width: Theme.iconSizeMedium
            height: Theme.iconSizeMedium
            source: _avatarSource
        }

        Label {
            id: titleLabel
            anchors.left: avatar.right
            anchors.right: parent.right
            anchors.leftMargin: Theme.paddingMedium
            color: wallItem.highlighted ? Theme.secondaryColor : Theme.secondaryHighlightColor
            font.bold: true
            font.pixelSize: Theme.fontSizeTiny
            truncationMode: TruncationMode.Fade
            text: _title
        }

        Loader {
            property var _wallpost: __wallpost
            property var _repost: wallpost.repost
            property bool isFeed: true
            anchors.top: titleLabel.bottom
            anchors.topMargin: Theme.paddingSmall
            width: parent.width
            active: true
            source: "../views/WallPostView.qml"
        }
    }

    menu: ContextMenu {

        MenuItem {
            text: qsTr("Like")
            onClicked: {
                vksdk.likes.addPost(sourceId, postId)
                isLiked = true
                likesCount += 1
            }
        }

        MenuItem {
            text: qsTr("Share")
            onClicked: {
                pageStack.push(Qt.resolvedUrl("../pages/RepostPage.qml"), { sourceId: sourceId,
                                                                   postId: wallpost.id })
            }
        }
    }

    onClicked: pageContainer.push(Qt.resolvedUrl("../pages/WallPostPage.qml"),
                                  { name: title, wallpost: wallpost })

    Component.onCompleted: {
        if (index === vksdk.newsfeedModel.size-1) vksdk.newsfeed.get(vksdk.newsfeedModel.next)
    }
}
