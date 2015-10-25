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
import "../js/api/messages.js" as MessagesAPI
import "../js/api/account.js" as AccountAPI
import "../js/storage.js" as StorageJS
import "../js/types.js" as TypesJS

CoverBackground {
    property int unreadDialogs: 0

    function updateCoverCounters(counter) {
        coverMessagesCount.text = counter ? counter : "0"
        if (counter !== unreadDialogs) notificationHelper.activateLed(counter > unreadDialogs)
        unreadDialogs = counter
        coverLoadingIndicator.running = false
    }

    Row {
        id: coverInfoPanel
        anchors.centerIn: parent
        spacing: 20

        Image {
            anchors.verticalCenter: coverMessagesCount.verticalCenter
            width: Theme.iconSizeSmall
            height: Theme.iconSizeSmall
            source: "image://theme/icon-l-email"
        }

        Label {
            id: coverMessagesCount
            text: "0"
            font.bold: true
            font.pixelSize: Theme.fontSizeHuge
        }
    }

    BusyIndicator {
        id: coverLoadingIndicator
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: false
    }

    CoverActionList {
        id: coverAction

        CoverAction {
            iconSource: "image://theme/icon-cover-new"

            onTriggered: {
                var pageComponent
                if (parseInt(StorageJS.readSettingsValue("create_from_cover"), 10) === 1) {
                    pageComponent = Qt.createQmlObject("import QtQuick 2.0; import \"../pages\"; Component { NewWallPostPage {} }", application)
                } else {
                    pageComponent = Qt.createQmlObject("import QtQuick 2.0; import \"../pages\"; Component { NewMessagePage {} }", application)
                }
                pageStack.push(pageComponent)
                window.activate()
            }
        }

        CoverAction {
            iconSource: "image://theme/icon-cover-refresh"

            onTriggered: updateTimer.restart()
        }
    }

    Timer {
        id: updateTimer
        running: !Qt.application.active
        repeat: true
        triggeredOnStart: true

        onRunningChanged: if (running) interval = TypesJS.UpdateInterval.getValue() * 1000
        onTriggered: {
            coverLoadingIndicator.running = true
            MessagesAPI.api_getUnreadMessagesCounter(true)
        }
    }

    Component.onCompleted: {
        MessagesAPI.signaller.gotUnreadCount.connect(updateCoverCounters)
    }
    Component.onDestruction: {
        MessagesAPI.signaller.gotUnreadCount.disconnect(updateUnreadMessagesCounter)
        AccountAPI.api_setOffline()
    }
}


