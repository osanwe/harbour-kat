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

import "../views"

Page {
    id: profilePage

    property var name
    property var wallpost

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: header.height + content.height

        PullDownMenu {

            MenuItem {
                text: qsTr("Like")
                onClicked: vksdk.likes.addPost(wallpost.sourceId, wallpost.id)
            }
        }

        PageHeader {
            id: header
            title: name
        }

        Column {
            id: content
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: header.bottom
            anchors.leftMargin: Theme.horizontalPageMargin
            anchors.rightMargin: Theme.horizontalPageMargin

            Loader {
                property var _wallpost: wallpost
                property var _repost: wallpost.repost
                property bool isFeed: false
                width: parent.width
                active: true
                source: "../views/WallPostView.qml"
            }
        }

        VerticalScrollDecorator {}
    }

    onStatusChanged: if (status === PageStatus.Active) pageStack.pushAttached(Qt.resolvedUrl("AudioPlayerPage.qml"))
}

