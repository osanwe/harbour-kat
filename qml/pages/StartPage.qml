/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import "../views"
import "../js/auth.js" as AuthJS
import "../js/storage.js" as StorageJS
import "../js/api/messages.js" as MessagesAPI
import "../js/api/users.js" as UsersAPI


Page {
    id: startPage

    function initialize() {
        StorageJS.initDatabase()
        if (!StorageJS.readSettingsValue("user_id")) {
            pageStack.push(Qt.resolvedUrl("LoginPage.qml"))
        } else {
            MessagesAPI.getDialogs(0)
        }
    }

    function doMainMenuItem() {
        if (StorageJS.readSettingsValue("user_id")) {
            console.log("Refreshing")
        } else {
            console.log("You have to sign in")
        }
    }

    function formMessagesList(title, message) {
        message = message.replace(/<br>/g, " ")
        var type = title === " ... " ? 0 : 1
        messagesList.model.append({ avatarSource: "", nameOrTitle: title, lastMessage: message , isChat: type})
    }

    property int chatsCounter: 0
    function updateDialogsList(index, avatarURL) {
        if (messagesList.model.get(parseInt(index, 10)+chatsCounter).isChat === 1) chatsCounter += 1
        messagesList.model.setProperty(parseInt(index, 10)+chatsCounter, "avatarSource", avatarURL)
    }

    SilicaListView {
        id: messagesList
        anchors.fill: parent
        model: ListModel {}
        delegate: DialogItem { id: dialogItem }

        PullDownMenu {
            MenuItem {
                id: mainMenuItem
                text: "Обновить"
                onClicked: doMainMenuItem()
            }
        }

        header: PageHeader {
            title: "Сообщения"
        }

        VerticalScrollDecorator {}
    }

    onPageContainerChanged: initialize()
}


