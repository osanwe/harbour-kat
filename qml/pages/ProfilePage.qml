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

    property var profileId
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

    function generateCountersModel() {
        countersGrid.model.clear()
        for (var index in counters) countersGrid.model.append(counters[index])
    }

    SilicaFlickable {
        anchors.fill: parent
        anchors.bottomMargin: Theme.paddingLarge
        contentHeight: content.height + header.height

        PullDownMenu {
            visible: (profile.id !== settings.userId()) && (profile.canWritePrivateMessage)

            MenuItem {
                visible: profile.canWritePrivateMessage
                text: qsTr("Go to dialog")
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("DialogPage.qml"), { chat: false,
                                                                       historyId: profile.id })
                }
            }
        }

        PageHeader {
            id: header
            title: profile.firstName + " " + profile.lastName

            Switch {
                anchors.verticalCenter: parent.verticalCenter
                automaticCheck: false
                checked: profile.online
            }
        }

        Column {
            id: content
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: header.bottom
            anchors.leftMargin: Theme.horizontalPageMargin
            anchors.rightMargin: Theme.horizontalPageMargin
            spacing: Theme.paddingLarge

            Row {
                width: parent.width
                spacing: Theme.paddingLarge

                Image {
                    width: Theme.iconSizeExtraLarge
                    height: Theme.iconSizeExtraLarge
                    source: profile.photo200

                    MouseArea {
                        anchors.fill: parent
                        onClicked: pageContainer.push(Qt.resolvedUrl("ImageViewPage.qml"),
                                                  { imagesModel: [profile.photoMaxOrig] })
                    }
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - Theme.iconSizeExtraLarge - Theme.paddingLarge
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
                                       pageContainer.push(Qt.resolvedUrl("FriendsListPage.qml"),
                                                      { userId: profile.id, type: 1 })
                                       break;

                                   case 7:
                                       pageContainer.push(Qt.resolvedUrl("FriendsListPage.qml"),
                                                      { userId: profile.id, type: 2 })
                                       break;

                                   case 8:
                                       pageContainer.push(Qt.resolvedUrl("FriendsListPage.qml"),
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
                        onClicked: pageContainer.replace(Qt.resolvedUrl("ProfilePage.qml"),
                                                         { profileId: profile.relationPartnerId } )
                    }
                }
            }
        }

        VerticalScrollDecorator {}
    }

    Connections {
        target: vksdk
        onGotProfile: {
            if (profileId === user.id) {
                profile = user
                generateCountersModel()
            }
        }
    }

    onStatusChanged: if (status === PageStatus.Active) pageStack.pushAttached(Qt.resolvedUrl("AudioPlayerPage.qml"))

    Component.onCompleted: {
        vksdk.users.getUserProfile(profileId)
    }
}

