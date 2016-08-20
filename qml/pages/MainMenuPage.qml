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

Page {
    id: mainMenuPage

    property var menuItems: [
        { itemText: qsTr("My profile"), counter: 0 },
        { itemText: qsTr("News"),       counter: 0 },
        { itemText: qsTr("Messages"),   counter: 0 },
        { itemText: qsTr("Friends"),   counter: 0 },
    ]

    /**
     *  The function does initial actions for showing menu and additional information.
     */
    function init() {
        busyIndicator.running = true
        for (var index in menuItems) menuList.model.append(menuItems[index])
        vksdk.users.getSelfProfile()
        vksdk.messages.getDialogs()
//        vksdk.longPoll.getLongPollServer()
    }

    /**
     * The function removes access token and user id from the config file.
     */
    function logout() {
        settings.removeAccessToken()
        settings.removeUserId()
        pageContainer.replace(Qt.resolvedUrl("LoginPage.qml"))
    }

    function openSubPage(menuItemIndex) {
        switch (menuItemIndex) {
        case 0: // Self profile page
            pageContainer.push(Qt.resolvedUrl("ProfilePage.qml"), { profileId: settings.userId() })
            break
        case 1: // Newsfeed page
            pageContainer.push(Qt.resolvedUrl("NewsfeedPage.qml"))
            break
        case 2: // Dialogs page
            pageContainer.push(Qt.resolvedUrl("DialogsListPage.qml"))
            break
        case 3: // Friends page
            pageContainer.push(Qt.resolvedUrl("FriendsListPage.qml"), { userId: settings.userId(),
                                                                        type:   1 })
            break
        }
    }

    BusyIndicator {
       id: busyIndicator
       anchors.centerIn: parent
       size: BusyIndicatorSize.Large
       running: false
    }

    SilicaListView {
        id: menuList
        anchors.fill: parent
        model: ListModel {}

        PullDownMenu {

//            MenuItem {
//                text: qsTr("About")
//            }

            MenuItem {
                text: qsTr("Logout")
                onClicked: logout()
            }

//            MenuItem {
//                text: qsTr("Settings")
//            }
        }

        header: PageHeader {}

        delegate: BackgroundItem {
            id: menuItem
            width: parent.width
            height: Theme.itemSizeSmall

            property var item: model.modelData ? model.modelData : model

            Row {
                anchors {
                    left: parent.left
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                }
                spacing: Theme.paddingMedium

                Label {
                    text: item.itemText
                    color: menuItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                }

                Rectangle {
                    width: menuItemCounter.width < menuItemCounter.height ?
                               menuItemCounter.height :
                               menuItemCounter.width + 2 * Theme.paddingSmall
                    height: menuItemCounter.height
                    radius: 10
                    color: menuItem.highlighted ? Theme.primaryColor : Theme.highlightColor
                    visible: item.counter !== 0

                    Label {
                        id: menuItemCounter
                        anchors.centerIn: parent
                        font.bold: true
                        color: menuItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                        text: item.counter
                    }
                }
            }

            onClicked: openSubPage(index)

//            onClicked: {
//                switch (index) {
//                case 0:
////                    pageContainer.push(Qt.resolvedUrl("ProfilePage.qml"),
////                                   { profileId: vksdk.selfProfile.id })
//                    break;

//                case 1:
////                    pageContainer.push(Qt.resolvedUrl("NewsfeedPage.qml"))
//                    break;

//                case 2:
////                    pageContainer.push(Qt.resolvedUrl("DialogsListPage.qml"))
//                    break;

//                case 3:
////                    pageContainer.push(Qt.resolvedUrl("FriendsListPage.qml"),
////                                       { userId: vksdk.selfProfile.id, type: 1 })
//                    break;
//                }
//            }
        }
    }

//    Connections {
//        target: vksdk.longPoll
//        onUnreadDialogsCounterUpdated: menuList.model.setProperty(2, "counter", value)
//    }

    Connections {
        target: vksdk
        onGotProfile: {
            if (status === PageStatus.Active) {
                busyIndicator.running = false
                menuList.headerItem.title = user.firstName + " " + user.lastName
            }
        }
        onGotUnreadCounter: menuList.model.setProperty(2, "counter", value)
    }

    onStatusChanged: if (status === PageStatus.Active) pageStack.pushAttached(Qt.resolvedUrl("AudioPlayerPage.qml"))

    Component.onCompleted: init()
}

