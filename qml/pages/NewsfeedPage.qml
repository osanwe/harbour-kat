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

import "../views"
import "../js/storage.js" as StorageJS
import "../js/api/news.js" as NewsAPI
import "../js/api/likes.js" as LikesAPI


Page {

    property string nextFrom

    property Item contextMenu

    function doStartUpdate() {
        if (StorageJS.readSettingsValue("user_id")) {
            loadingIndicator.running = true
            newsfeedList.model.clear()
            nextFrom = ""
            NewsAPI.api_getLastNews(nextFrom)
        }
    }

    function appendPostToNewsFeed(postData) {
        newsfeedList.model.append({ postId:          postData[0],
                                    textBody:        postData[1],
                                    out:             0,
                                    readState:       1,
                                    datetime:        postData[2],
                                    attachmentsData: postData.slice(6),
                                    avatarSource:    postData[3],
                                    postAuthor:      postData[4],
                                    sourceId:        postData[5],
                                    isNewsContent:   true })
    }

    function stopLoadingNewsIndicator(next_from) {
        if (typeof next_from !== 'undefined') nextFrom = next_from
        loadingIndicator.running = false
    }

    function shownotification(text) {
        notificationHelper.sendNotification("", text)
    }

    BusyIndicator {
        id: loadingIndicator
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: false // true
    }

    SilicaListView {
        id: newsfeedList
        anchors.fill: parent

        PullDownMenu {

    //            MenuItem {
    //                text: "Написать"
    //                onClicked:
    //            }

            MenuItem {
                text: qsTr("Обновить")
                onClicked: doStartUpdate()
            }
        }

        model: ListModel {}

        header: PageHeader { title: qsTr("Новости") }

        delegate: Item {
            id: newsItem

            property bool menuOpen: contextMenu != null && contextMenu.parent === newsItem

            width: parent.width
            height: menuOpen ? contextMenu.height + contentItem.height : contentItem.height

            PostItem {
                id: contentItem
                width: parent.width

                onClicked: pageContainer.push(Qt.resolvedUrl("../pages/OneNewsPage.qml"),
                                              { "datetime":        datetime,
                                                "textBody":        textBody,
                                                "postAuthor":      postAuthor,
                                                "itemId":          postId,
                                                "ownerId":         sourceId,
                                                "attachmentsData": attachmentsData })
                onPressAndHold: {
                    if (!contextMenu)
                        contextMenu = contextMenuComponent.createObject(newsfeedList)
                    contextMenu.show(newsItem)
                }
            }

            Component {
                id: contextMenuComponent

                ContextMenu {

                    MenuItem {
                        text: qsTr("Мне нравится")
                        onClicked: LikesAPI.api_addLike("post", newsfeedList.model.get(index).postId, newsfeedList.model.get(index).sourceId)
                    }

                    onClosed: contextMenu = null
                }
            }
        }

//        delegate: PostItem {
//            width: parent.width
//        }

        footer: Button {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width / 3 * 2
            text: qsTr("Загрузить больше")
            visible: nextFrom !== ''

            onClicked: {
                loadingIndicator.running = true
                NewsAPI.api_getLastNews(nextFrom)
            }
        }

        VerticalScrollDecorator {}
    }

    Component.onCompleted: {
        doStartUpdate()
    }
}
