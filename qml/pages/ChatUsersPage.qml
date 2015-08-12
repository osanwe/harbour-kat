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
import "../js/api/messages.js" as MessagesAPI


Page {
    id: chatUsersPage

//    property int dialogId
    property string chatTitle
    property variant users

    function appendUser(uid, name, photo, isOnline, status) {
        usersList.model.append({ dialogId:     uid,
                                 isDialog:     false,
                                 avatarSource: photo,
                                 nameOrTitle:  name,
                                 previewText:  status,
                                 isOnline:     isOnline })
    }

    SilicaListView {
        id: usersList
        anchors.fill: parent
        anchors.bottomMargin: Theme.paddingMedium

        model: ListModel {}

        delegate: UserItem {}

        header: PageHeader {
            title: chatTitle
        }

        VerticalScrollDecorator {}
    }

//    Component.onCompleted: MessagesAPI.api_getChatUsers(dialogId)
    Component.onCompleted: {
        for (var index in users) {
            usersList.model.append({ dialogId:     users[index].id,
                                     isDialog:     false,
                                     avatarSource: users[index].photo,
                                     nameOrTitle:  users[index].name,
                                     previewText:  users[index].status,
                                     isOnline:     users[index].online })
        }
    }
}
