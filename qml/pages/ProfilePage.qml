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
    id: profilePage

    property var profile

    property var counters: [
        { index: 0, title: qsTr("Photos"), counter: profile.photosCounter },
        { index: 1, title: qsTr("Videos"), counter: profile.videosCounter },
        { index: 2, title: qsTr("Audios"), counter: profile.audiosCounter },
        { index: 3, title: qsTr("Groups"), counter: profile.groupsCounter },
        { index: 4, title: qsTr("Pages"), counter: profile.pagesCounter },
        { index: 5, title: qsTr("Followers"), counter: profile.followersCounter },
        { index: 6, title: qsTr("Friends"), counter: profile.friendsCounter },
        { index: 7, title: qsTr("Online friends"), counter: profile.onlineFriendsCounter },
        { index: 8, title: qsTr("Mutual Friends"), counter: profile.mutualFriendsCounter },
        { index: 9, title: qsTr("Notes"), counter: profile.notesCounter }
    ]

    SilicaFlickable {
        anchors.fill: parent

        Column {
            anchors.fill: parent
            anchors.leftMargin: Theme.horizontalPageMargin
            anchors.rightMargin: Theme.horizontalPageMargin
            spacing: Theme.paddingLarge

            PageHeader {
                title: profile.firstName + " " + profile.lastName

                Switch {
                    anchors.verticalCenter: parent.verticalCenter
                    automaticCheck: false
                    checked: profile.online
                }
            }

            Row {
                width: parent.width
                spacing: Theme.paddingLarge

                Image {
                    width: Theme.iconSizeExtraLarge
                    height: Theme.iconSizeExtraLarge
                    source: profile.photo200

                    MouseArea {
                        anchors.fill: parent
                        onClicked: pageStack.push(Qt.resolvedUrl("ImageViewPage.qml"), { photoSource: profile.photoMaxOrig })
                    }
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - Theme.iconSizeExtraLarge - Theme.paddingLarge
//                    height: Theme.iconSizeExtraLarge
                    color: Theme.secondaryColor
                    maximumLineCount: 4
                    wrapMode: Text.WordWrap
                    truncationMode: TruncationMode.Fade
                    font.pixelSize: Theme.fontSizeExtraSmall
                    text: profile.status
                }
            }

            Flow {
                width: parent.width

                Repeater {
                    id: countersGrid
                    model: ListModel {}

                    delegate: BackgroundItem {
                        id: counterItem

                        property var item: model.modelData ? model.modelData : model

                        width: Theme.itemSizeMedium + 2 * Theme.paddingMedium
                        height: Theme.itemSizeMedium + 2 * Theme.paddingMedium
                        visible: item.counter > 0

                        Column {
                            anchors.fill: parent
                            anchors.leftMargin: Theme.paddingMedium
                            anchors.rightMargin: Theme.paddingMedium
                            anchors.topMargin: Theme.paddingMedium
                            anchors.bottomMargin: Theme.paddingMedium

                            Label {
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: parent.width
                                truncationMode: TruncationMode.Fade
                                font.bold: true
                                color: counterItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                                text: item.title
                            }

                            Label {
                                anchors.horizontalCenter: parent.horizontalCenter
                                width: parent.width
                                truncationMode: TruncationMode.Fade
                                color: counterItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                                text: item.counter
                            }
                        }

                        onClicked: switch (item.index) {
                                   case 6:
                                       pageStack.push(Qt.resolvedUrl("FriendsListPage.qml"),
                                                      { userId: profile.id, type: 1 })
                                       break;

                                   case 7:
                                       pageStack.push(Qt.resolvedUrl("FriendsListPage.qml"),
                                                      { userId: profile.id, type: 2 })
                                       break;

                                   case 8:
                                       pageStack.push(Qt.resolvedUrl("FriendsListPage.qml"),
                                                      { userId: profile.id, type: 3 })
                                       break;
                                   }
                    }
                }
            }

            Row {
                width: parent.width
                spacing: Theme.paddingSmall
                visible: profile.sex !== 0

                Label {
                    font.bold: true
                    text: qsTr("Gender:")
                }

                Label {
                    text: profile.sex === 1 ? qsTr("Female") : qsTr("Male")
                }
            }

            Row {
                width: parent.width
                spacing: Theme.paddingSmall
                visible: profile.bdate !== ""

                Label {
                    font.bold: true
                    text: qsTr("Birthday:")
                }

                Label {
                    text: profile.bdate
                }
            }

            Row {
                width: parent.width
                spacing: Theme.paddingSmall
                visible: profile.city !== ""

                Label {
                    font.bold: true
                    text: qsTr("City:")
                }

                Label {
                    text: profile.city
                }
            }

            Row {
                width: parent.width
                spacing: Theme.paddingSmall
                visible: profile.relation !== 0

                Label {
                    font.bold: true
                    text: switch (profile.relation) {
                          case 1:
                              return qsTr("Single")

                          case 2:
                              return qsTr("In a relationship")

                          case 3:
                              return qsTr("Engaged")

                          case 4:
                              return qsTr("Married")

                          case 5:
                              return qsTr("It's complicated")

                          case 6:
                              return qsTr("Actively searching")

                          case 7:
                              return qsTr("In love")
                          }
                }

                Label {
                    font.underline: true
                    color: Theme.highlightColor
                    text: profile.relationPartnerName

                    MouseArea {
                        anchors.fill: parent
                        onClicked: vksdk.users.getUserProfile(profile.relationPartnerId)
                    }
                }
            }
        }
    }

    Connections {
        target: vksdk
        onGotProfile: pageStack.push(Qt.resolvedUrl("ProfilePage.qml"), { profile: user })
        onGotSelfProfile: pageStack.push(Qt.resolvedUrl("ProfilePage.qml"), { profile: vksdk.selfProfile })
    }

    Component.onCompleted: {
        for (var index in counters) countersGrid.model.append(counters[index])
    }
}

