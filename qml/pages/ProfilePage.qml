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

    property var profileId
    property var profile

    property var counters: [
        { index: 0, title: qsTr("Photos"), counter: profile.photosCounter },
        { index: 1, title: qsTr("Videos"), counter: profile.videosCounter },
        { index: 5, title: qsTr("Followers"), counter: profile.followersCounter },
        { index: 9, title: qsTr("Notes"), counter: profile.notesCounter }
    ]

    function generateCountersModel() {
//        countersGrid.model.clear()
//        for (var index in counters) countersGrid.model.append(counters[index])
    }

    SilicaFlickable {
        anchors.fill: parent
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

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 2 * Theme.horizontalPageMargin
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

            CollapsedView {
                id: profileInfo
                width: parent.width
                bdate: profile.bdate
                relation: profile.relation
                relationPartnerName: profile.relationPartnerName
                relationPartnerId: profile.relationPartnerId
                city: profile.city
                sex: profile.sex
            }

            MoreButton {
                id: friendsButton
                width: parent.width
                height: Theme.itemSizeMedium
                text: qsTr("Friends") /*+ " (" + profile.friendsCounter + ")"*/
                counter: profile.friendsCounter

                onClicked: pageContainer.push(Qt.resolvedUrl("FriendsListPage.qml"),
                                              { userId: profile.id, type: 1 })
            }

            MoreButton {
                id: audiosButton
                width: parent.width
                height: Theme.itemSizeMedium
                text: qsTr("Audios") /*+ " (" + profile.audiosCounter + ")"*/
                counter: profile.audiosCounter

                onClicked: {
                    vksdk.audios.get(profileId)
                    pageContainer.navigateForward()
                }
            }

            MoreButton {
                id: groupsButton
                width: parent.width
                height: Theme.itemSizeMedium
                text: qsTr("Groups") /*+ " (" + profile.groupsCounter + ")"*/
                counter: profile.groupsCounter

                onClicked: pageContainer.push(Qt.resolvedUrl("GroupsListPage.qml"),
                                              { userId: profile.id })
            }

            MoreButton {
                id: wallButton
                width: parent.width
                height: Theme.itemSizeMedium
                text: qsTr("Wall") /*+ " (" + vksdk.wallModel.count + ")"*/
                counter: vksdk.wallModel.count
                isopen: true
            }

            ListView {
                id: walllist
                width: parent.width
                height: contentHeight
                model: vksdk.wallModel
                delegate: Component {

                    Loader {
                        property var _avatarSource: avatarSource
                        property var _title: title
                        property var __wallpost: wallpost
                        width: parent.width
                        sourceComponent: wallitem
                    }
                }
            }
        }

        PushUpMenu {
            visible: walllist.count !== vksdk.wallModel.count

            MenuItem {
                text: qsTr("Load more")
                onClicked: vksdk.wall.get(profileId, walllist.count)
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

    onStatusChanged: {
        if (status === PageStatus.Active) {
            pageStack.pushAttached(Qt.resolvedUrl("AudioPlayerPage.qml"))
            if (vksdk.wallModel.id !== profileId) {
                vksdk.wallModel.clear()
                vksdk.wallModel.id = profileId
                vksdk.wall.get(profileId)
            }
        }
    }

    Component.onCompleted: {
        vksdk.users.getUserProfile(profileId)
    }

    Component {
        id: wallitem
        ListItem {
            id: newsfeedItem
            width: parent.width
            contentHeight: wallcontent.height + Theme.paddingLarge
//            height: content.height + Theme.paddingLarge

            Item {
                id: wallcontent
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

                Column {
                    anchors.left: avatar.right
                    anchors.right: parent.right
                    anchors.leftMargin: Theme.paddingMedium
                    spacing: Theme.paddingSmall

                    Label {
                        width: parent.width
                        color: newsfeedItem.highlighted ? Theme.secondaryColor : Theme.secondaryHighlightColor
                        font.bold: true
                        font.pixelSize: Theme.fontSizeTiny
                        truncationMode: TruncationMode.Fade
                        text: _title
                    }

                    Loader {
                        property var _wallpost: __wallpost
                        property var _repost: __wallpost.repost
                        property bool isFeed: true
                        width: parent.width
                        active: true
                        source: "../views/WallPostView.qml"
                    }
                }
            }

            menu: ContextMenu {

                MenuItem {
                    text: qsTr("Like")
                    onClicked: {
                        vksdk.likes.addPost(sourceId, postId)
//                        isLiked = true
//                        likesCount += 1
                    }
                }
            }

            onClicked: pageContainer.push(Qt.resolvedUrl("WallPostPage.qml"),
                                          { name: _title, wallpost: __wallpost })
        }
    }
}

