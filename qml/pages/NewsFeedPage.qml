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

    property string nextFrom

    function doStartUpdate() {
        loadingNewsIndicator.running = true
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
        loadingNewsIndicator.running = false
    }

    BusyIndicator {
        id: loadingNewsIndicator
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: false // true
    }

    Drawer {
        id: drawer
        anchors.fill: parent
        open: true
        dock: Dock.Left

        background: SilicaListView {
            anchors.fill: parent

            model: ListModel {

                ListElement {
                    icon: "image://theme/icon-l-message"
                    name: "Новости"
                    counter: ""
                }

                ListElement {
                    icon: "image://theme/icon-l-redirect"
                    name: "Ответы"
                    counter: "0"
                }

                ListElement {
                    icon: "image://theme/icon-l-email"
                    name: "Сообщения"
                    counter: "0"
                }

                ListElement {
                    icon: "image://theme/icon-l-people"
                    name: "Друзья"
                    counter: "0"
                }

                ListElement {
                    icon: "image://theme/icon-l-people"
                    name: "Группы"
                    counter: "0"
                }

                ListElement {
                    icon: "image://theme/icon-l-image"
                    name: "Фотографии"
                    counter: "0"
                }

                ListElement {
                    icon: "image://theme/icon-l-video"
                    name: "Видеозаписи"
                    counter: "0"
                }

                ListElement {
                    icon: "image://theme/icon-l-music"
                    name: "Аудиозаписи"
                    counter: ""
                }

                ListElement {
                    icon: "image://theme/icon-l-favorite"
                    name: "Закладки"
                    counter: ""
                }

                ListElement {
                    icon: "image://theme/icon-l-document"
                    name: "Документы"
                    counter: ""
                }

                ListElement {
                    icon: "image://theme/icon-cover-search"
                    name: "Поиск"
                    counter: ""
                }
            }

            header: BackgroundItem {
                width: parent.width
                height: Theme.itemSizeMedium

                Image {
                    id: userAvatar
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.paddingLarge
                    anchors.verticalCenter: parent.verticalCenter
                    width: Theme.itemSizeMedium - 2 * Theme.paddingMedium
                    height: Theme.itemSizeMedium - 2 * Theme.paddingMedium
                    source: userAvatarUrl

                    Connections {
                        target: fileDownloader
                        onDownloaded: {
                            userAvatarUrl = "/home/nemo/.cache/harbour-kat/" + StorageJS.readUserAvatar()
                            userAvatar.source = userAvatarUrl
                        }
                    }
                }

                Label {
                    id: userName
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: Theme.fontSizeLarge
                    height: Theme.itemSizeMedium
                    verticalAlignment: Text.AlignVCenter
                    color: Theme.highlightColor
                    text: userFullName
                }
            }

            delegate: BackgroundItem {
                id: menuItem
                height: Theme.itemSizeSmall

                Item {
                    anchors.fill: parent
                    anchors.rightMargin: Theme.paddingLarge
                    anchors.leftMargin: Theme.paddingLarge

                    Image {
                        id: menuItemIcon
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        width: Theme.iconSizeSmall
                        height: Theme.iconSizeSmall
                        source: icon
                    }

                    Label {
                        anchors.left: menuItemIcon.right
                        anchors.right: menuItemCounter.left
                        anchors.leftMargin: Theme.paddingMedium
                        anchors.rightMargin: menuItemCounter.text.length > 0 ? Theme.paddingMedium : 0
                        anchors.verticalCenter: parent.verticalCenter
                        color: menuItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                        maximumLineCount: 1
                        truncationMode: TruncationMode.Fade
                        text: name
                    }

                    Label {
                        id: menuItemCounter
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                        color: menuItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                        text: counter
                    }
                }
            }

            VerticalScrollDecorator {}
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
                            drawer.open = (xPos < mouseX)
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
    //                MessagesAPI.api_getDialogsList(dialogsOffset)
                }
            }

            VerticalScrollDecorator {}
        }
    }

//    onStatusChanged: if (status === PageStatus.Active) doStartUpdate()
    Component.onCompleted: doStartUpdate()
}
