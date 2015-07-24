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

import "../js/api/news.js" as NewsAPI


SilicaListView {
    id: newsfeedList
    anchors.fill: parent

    property string nextFrom

    function doStartUpdate() {
        loadingIndicator.running = true
        newsfeedList.model.clear()
        nextFrom = ""
        NewsAPI.api_getLastNews(nextFrom)
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

    function stopLoadingNewsIndicator(next_from) {
        nextFrom = next_from
        loadingIndicator.running = false
    }

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

    model: ListModel {}

    header: PageHeader { title: "Новости" }

    delegate: PostItem {
        width: parent.width

        MouseArea {
            anchors.fill: parent

            property real xPos
            property real yPos

            onPressed: { xPos = mouseX; yPos = mouseY; }
            onReleased:
                if (xPos == mouseX && yPos == mouseY) {
                    pageContainer.push(Qt.resolvedUrl("OneNewsPage.qml"),
                                       { "datetime":        datetime,
                                         "textBody":        textBody,
                                         "postAuthor":      postAuthor,
                                         "attachmentsData": attachmentsData })
                } else {
                    var delta = mouseX - xPos
                    var idealDelta = Screen.width / 4
                    if (Math.abs(delta) >= idealDelta) drawer.open = (delta > 0)
                }
        }
    }

    footer: Button {
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width / 3 * 2
        text: "Загрузить больше"

        onClicked: {
            loadingNewsIndicator.running = true
            NewsAPI.api_getLastNews(nextFrom)
        }
    }

    VerticalScrollDecorator {}

    Component.onCompleted: doStartUpdate()
}
