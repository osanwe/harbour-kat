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
    id: dialogPage

    property var profile

    SilicaListView {
        id: messagesListView
        anchors.fill: parent
        anchors.bottomMargin: Theme.paddingMedium + message_text.height
        verticalLayoutDirection: ListView.BottomToTop
        clip: true
        delegate: MessageItem {
            isOut: model.modelData.out
            avatarSource: model.modelData.out ? vksdk.selfProfile.photo50 : profile.photo50
            bodyText: model.modelData.body
        }

        VerticalScrollDecorator {}
    }

    Row {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin
        spacing: Theme.paddingMedium

        TextField {
            id: message_text
            width: parent.width - attachButton.width - parent.spacing
            placeholderText: qsTr("Your message")
            label: qsTr("Your message")

            EnterKey.enabled: text.length > 0
            EnterKey.iconSource: "image://theme/icon-m-enter-accept"
            EnterKey.onClicked: emailField.focus = true
        }


        IconButton {
            id: attachButton
            width: Theme.iconSizeMedium
            height: Theme.iconSizeMedium
            icon.source: "image://theme/icon-m-attach"

            onClicked: console.log("attach")
        }
    }

    Connections {
        target: vksdk
        onGotMessages: messagesListView.model = messages
    }

    Component.onCompleted: vksdk.messages.getHistory(profile.id)
}

