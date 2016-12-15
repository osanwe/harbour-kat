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

    ViewPlaceholder {
        id: systemMessage
        enabled: false
    }

    SilicaFlickable {
        id: userDataView
        anchors.fill: parent
        contentHeight: content.height + header.height

        PullDownMenu {

            MenuItem {
                visible: profile.domain.length > 0
                text: qsTr("Open in browser")
                onClicked: Qt.openUrlExternally("https://m.vk.com/" + profile.domain)
            }

            MenuItem {
                text: profile.blacklisted ? qsTr("Remove from blacklist") : qsTr("Add to blacklist")
                onClicked: console.log("...banning...")
            }

            MenuItem {
                text: profile.isFavorite ? qsTr("Remove from favorites") : qsTr("Add to favorites")
                onClicked: console.log("...favoriting...")
            }

            MenuItem {
                text: {
                    switch (profile.friendStatus) {
                    case 0:
                        if (!profile.canSendFriendRequest) visible = false
                        return qsTr("Add to friends")
                    case 2:
                        return qsTr("Add to friends")
                    case 1:
                        return qsTr("Cancel friend request")
                    case 3:
                        return qsTr("Remove from friends")
                    }
                }
                onClicked: console.log("...friending...")
            }

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
            title: "Имя Отчество\nФамилия (Фамилия)"

            Column {
                anchors.verticalCenter: parent.verticalCenter

                Switch {
                    id: onlineStatusView
                    automaticCheck: false
//                    checked: profile.online
                }

                Image {
                    width: onlineStatusView.width
                    height: onlineStatusView.width
                    source: "image://theme/icon-s-installed"
                    visible: profile.verified
                }
            }
        }

        Column {
            id: content
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: header.bottom

//            Row {
//                anchors.horizontalCenter: parent.horizontalCenter
//                width: parent.width - 2 * Theme.horizontalPageMargin
//                spacing: Theme.paddingLarge

//                Image {
//                    width: Theme.iconSizeExtraLarge
//                    height: Theme.iconSizeExtraLarge
//                    source: profile.photo200

//                    MouseArea {
//                        anchors.fill: parent
//                        onClicked: pageContainer.push(Qt.resolvedUrl("ImageViewPage.qml"),
//                                                  { imagesModel: [profile.photoMaxOrig] })
//                    }
//                }

//                Label {
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: parent.width - Theme.iconSizeExtraLarge - Theme.paddingLarge
//                    color: Theme.secondaryColor
//                    maximumLineCount: 4
//                    wrapMode: Text.WordWrap
//                    truncationMode: TruncationMode.Fade
//                    font.pixelSize: Theme.fontSizeExtraSmall
//                    text: profile.status
//                }
//            }

//            CollapsedView {
//                id: profileInfo
//                width: parent.width
//                bdate: profile.bdate
//                relation: profile.relation
//                relationPartnerName: profile.relationPartnerName
//                relationPartnerId: profile.relationPartnerId
//                city: profile.city
//                sex: profile.sex
//            }

//            MoreButton {
//                id: friendsButton
//                width: parent.width
//                height: Theme.itemSizeMedium
//                text: qsTr("Friends") /*+ " (" + profile.friendsCounter + ")"*/
//                counter: profile.friendsCounter

//                onClicked: pageContainer.push(Qt.resolvedUrl("FriendsListPage.qml"),
//                                              { userId: profile.id, type: 1 })
//            }

//            MoreButton {
//                id: audiosButton
//                width: parent.width
//                height: Theme.itemSizeMedium
//                text: qsTr("Audios") /*+ " (" + profile.audiosCounter + ")"*/
//                counter: profile.audiosCounter

//                onClicked: {
//                    vksdk.audios.get(profileId)
//                    pageContainer.navigateForward()
//                }
//            }

//            MoreButton {
//                id: groupsButton
//                width: parent.width
//                height: Theme.itemSizeMedium
//                text: qsTr("Groups") /*+ " (" + profile.groupsCounter + ")"*/
//                counter: profile.groupsCounter

//                onClicked: pageContainer.push(Qt.resolvedUrl("GroupsListPage.qml"),
//                                              { userId: profile.id })
//            }

//            MoreButton {
//                id: wallButton
//                width: parent.width
//                height: Theme.itemSizeMedium
//                text: qsTr("Wall") /*+ " (" + vksdk.wallModel.count + ")"*/
//                counter: vksdk.wallModel.count
//                isopen: true
//            }

//            ListView {
//                id: walllist
//                width: parent.width
//                height: contentHeight
//                model: vksdk.wallModel
//                delegate: Component {

//                    Loader {
//                        property var _avatarSource: avatarSource
//                        property var _title: title
//                        property var __wallpost: wallpost
//                        width: parent.width
//                        source: "../views/WallItem.qml"
//                    }
//                }
//            }
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
                if (profile.deactivated.length > 0) {
                    userDataView.visible = false
                    systemMessage.enabled = true
                    if (profile.deactivated === "deleted") systemMessage.text = qsTr("The user is deleted")
                    else if (profile.deactivated === "banned") systemMessage.text = qsTr("The user was baned")
                }
            }
        }
    }

    onStatusChanged: {
        if (status === PageStatus.Active) {
//            pageStack.pushAttached(Qt.resolvedUrl("AudioPlayerPage.qml"))
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
}
