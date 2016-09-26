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

    property var groupId
    property var group

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: content.height + header.height

//        PullDownMenu {
//            visible: (profile.id !== settings.userId()) && (profile.canWritePrivateMessage)

//            MenuItem {
//                visible: profile.canWritePrivateMessage
//                text: qsTr("Go to dialog")
//                onClicked: {
//                    pageStack.push(Qt.resolvedUrl("DialogPage.qml"), { chat: false,
//                                                                       historyId: profile.id })
//                }
//            }
//        }

        PageHeader {
            id: header
            title: group.name
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
                    source: group.photo200

                    MouseArea {
                        anchors.fill: parent
                        onClicked: pageContainer.push(Qt.resolvedUrl("ImageViewPage.qml"),
                                                  { imagesModel: [group.photoMaxOrig] })
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
                    text: group.status
                }
            }

            CollapsedView {
                id: profileInfo
                width: parent.width
                description: group.description
            }

            MoreButton {
                width: parent.width
                height: Theme.itemSizeMedium
                text: qsTr("Members")
                counter: group.membersCount
            }

            MoreButton {
                width: parent.width
                height: Theme.itemSizeMedium
                text: qsTr("Photos")
                counter: group.photosCount
                visible: group.photosCount !== 0
            }

            MoreButton {
                width: parent.width
                height: Theme.itemSizeMedium
                text: qsTr("Audios")
                counter: group.audiosCount
                visible: group.audiosCount !== 0
            }

            MoreButton {
                width: parent.width
                height: Theme.itemSizeMedium
                text: qsTr("Videos")
                counter: group.videosCount
                visible: group.videosCount !== 0
            }

            MoreButton {
                width: parent.width
                height: Theme.itemSizeMedium
                text: qsTr("Topics")
                counter: group.topicsCount
                visible: group.topicsCount !== 0
            }

            MoreButton {
                width: parent.width
                height: Theme.itemSizeMedium
                text: qsTr("Documents")
                counter: group.docsCount
                visible: group.docsCount !== 0
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
                onClicked: vksdk.wall.get(groupId, walllist.count)
            }
        }

        VerticalScrollDecorator {}
    }

    Connections {
        target: vksdk
        onGotGroup: group = grp
    }

    onStatusChanged: {
        if (status === PageStatus.Active) {
            pageStack.pushAttached(Qt.resolvedUrl("AudioPlayerPage.qml"))
            if (vksdk.wallModel.id !== groupId) {
                vksdk.wallModel.clear()
                vksdk.wallModel.id = groupId
                vksdk.wall.get(groupId)
            }
        }
    }

    Component.onCompleted: {
        vksdk.groups.getById(groupId)
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
