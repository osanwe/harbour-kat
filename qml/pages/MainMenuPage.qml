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
        { itemText: qsTr("News"),     counter: 0 },
        { itemText: qsTr("Messages"), counter: 0 }
    ]

    function generateModelFromArray() {
        for (var index in menuItems)
            menuList.model.append(menuItems[index])
    }

    SilicaListView {
        id: menuList

        anchors.fill: parent

        model: ListModel {}

        PullDownMenu {

            MenuItem {
                text: qsTr("About")
            }

            MenuItem {
                text: qsTr("Logout")
                onClicked: {
                    settings.removeAccessToken()
                    pageStack.replace(Qt.resolvedUrl("LoginPage.qml"))
                }
            }

            MenuItem {
                text: qsTr("Settings")
            }
        }

        header: PageHeader {}

        delegate: BackgroundItem {
            id: menuItem
            width: parent.width
            height: Theme.itemSizeMedium

            property var item: model.modelData ? model.modelData : model

            Row {
                spacing: Theme.paddingMedium
                anchors {
                    left: parent.left
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                }

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

            onClicked: {
                switch (index) {
                case 0:
                    break;

                case 1:
                    pageStack.push(Qt.resolvedUrl("DialogsListPage.qml"))
                    break;
                }
            }
        }
    }

    Connections {
        target: vksdk.longPoll
        onUnreadDialogsCounterUpdated: menuList.model.setProperty(1, "counter", value)
    }

    Component.onCompleted: {
        generateModelFromArray()
        vksdk.longPoll.getLongPollServer()
        vksdk.messages.getDialogs()
    }
}

