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
    id: newfeedPage

    BusyIndicator {
       id: busyIndicator
       anchors.centerIn: parent
       size: BusyIndicatorSize.Large
       running: false
    }

    SilicaListView {
        id: newsfeed
        anchors.fill: parent
        model: vksdk.newsfeedModel

        header: PageHeader {
            title: qsTr("Newsfeed")
        }

        delegate: ListItem {
            id: newsfeedItem
            width: parent.width
            contentHeight: content.height + Theme.paddingLarge
//            height: content.height + Theme.paddingLarge

            Item {
                id: content
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
                    source: avatarSource
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
                        text: title
                    }

                    Row {
                        width: parent.width
                        spacing: Theme.paddingSmall

                        Label {
                            width: parent.width - comments.width - likes.width - reposts.width - 3 * Theme.fontSizeTiny - 6 * Theme.paddingSmall
                            color: newsfeedItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                            font.pixelSize: Theme.fontSizeTiny
                            text: convertUnixtimeToString(datetime)
                        }

                        Image {
                            width: Theme.fontSizeTiny
                            height: Theme.fontSizeTiny
                            source: "image://theme/icon-s-chat?" +
                                    (newsfeedItem.highlighted ? Theme.secondaryHighlightColor :
                                                                Theme.secondaryColor)
                        }

                        Label {
                            id: comments
                            color: newsfeedItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                            font.pixelSize: Theme.fontSizeTiny
                            text: commentsCount
                        }

                        Image {
                            width: Theme.fontSizeTiny
                            height: Theme.fontSizeTiny
                            source: "image://theme/icon-s-like?" +
                                    (newsfeedItem.highlighted || isLiked ?
                                         Theme.secondaryHighlightColor : Theme.secondaryColor)
                        }

                        Label {
                            id: likes
                            color: newsfeedItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                            font.pixelSize: Theme.fontSizeTiny
                            text: likesCount
                        }

                        Image {
                            width: Theme.fontSizeTiny
                            height: Theme.fontSizeTiny
                            source: "image://theme/icon-s-retweet?" +
                                    (newsfeedItem.highlighted || isReposted ?
                                         Theme.secondaryHighlightColor : Theme.secondaryColor)
                        }

                        Label {
                            id: reposts
                            color: newsfeedItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                            font.pixelSize: Theme.fontSizeTiny
                            text: repostsCount
                        }
                    }

                    Label {
                        width: parent.width
                        wrapMode: Text.WordWrap
                        maximumLineCount: 5
                        truncationMode: TruncationMode.Fade
                        color: newsfeedItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                        text: newsText
                    }
                }
            }

            menu: ContextMenu {

                MenuItem {
                    text: qsTr("Like")
                    onClicked: {
                        vksdk.likes.addPost(sourceId, postId)
                        isLiked = true
                        likesCount += 1
                    }
                }
            }

            onClicked: pageContainer.push(Qt.resolvedUrl("WallPostPage.qml"), { wallpost: wallpost })

            Component.onCompleted: {
                if (index === vksdk.newsfeedModel.size-1) vksdk.newsfeed.get(vksdk.newsfeedModel.next)
            }
        }

        VerticalScrollDecorator {}
    }

    Component.onCompleted: vksdk.newsfeed.get()
}

