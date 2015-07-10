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
import "../js/api/news.js" as NewsAPI


Page {

    function doStartUpdate() {
        loadingNewsIndicator.running = true
        newsfeedList.model.clear()
        NewsAPI.api_getLastNews(null)
    }

    function appendPostToNewsFeed(postData) {
        newsfeedList.model.append({ textBody:        postData[1],
                                    out:             0,
                                    readState:       1,
                                    datetime:        postData[2],
                                    attachmentsData: postData.slice(5),
                                    avatarSource:    postData[3],
                                    postAuthor:      postData[4],
                                    isNewsContent:   true })
    }

    function stopLoadingNewsIndicator() {
        loadingNewsIndicator.running = false
    }

    BusyIndicator {
        id: loadingNewsIndicator
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: true
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
                text: "Обновить"
                onClicked: doStartUpdate()
            }
        }

        header: PageHeader { title: "Новости" }

        model: ListModel {}

        delegate: PostItem {
            width: parent.width

            onClicked: pageContainer.push(Qt.resolvedUrl("OneNewsPage.qml"),
                                          { "datetime": datetime,
                                            "textBody": textBody,
                                            "postAuthor": postAuthor,
                                            "attachmentsData": attachmentsData })
        }

        VerticalScrollDecorator {}
    }

//    onStatusChanged: if (status === PageStatus.Active) doStartUpdate()
    Component.onCompleted: doStartUpdate()
}
