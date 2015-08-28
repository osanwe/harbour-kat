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
import QtMultimedia 5.0
import Sailfish.Silica 1.0

import "../js/storage.js" as StorageJS

BackgroundItem {
    anchors.left: parent.left
    anchors.right: parent.right
    height: Math.max(authorAvatar.height, mainContent.height) + 2 * Theme.paddingMedium

    function playAudio(url) {
        audioPlayer.source = url
        audioPlayer.play()
    }

    function getVideoUrl(urls, quality) {
        var url = ""
        switch (quality) {
        case 0:
            url = urls.mp4_720
            break;

        case 1:
            url = urls.mp4_480
            break;

        case 2:
            url = urls.mp4_360
            break;

        case 3:
            url = urls.mp4_240
            break;
        }
        if (url) {
            return url
        } else if (quality < 3) {
            return getVideoUrl(urls, quality+1)
        } else {
            return
        }
    }

    function openVideoPlayer(urls, duration) {
        console.log(urls)
        console.log(duration)
        var url = getVideoUrl(urls, parseInt(StorageJS.readSettingsValue("video_quality"), 10))
//        console.log(url)

        if (url) {
            pageContainer.push("../pages/VideoPage.qml", { "url": url, "duration": duration })
        } else if (urls.external) {
            Qt.openUrlExternally(urls.external)
        }
    }

    Audio {
        id: audioPlayer
    }

    Separator {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: Theme.paddingMedium
        anchors.rightMargin: Theme.paddingMedium
        color: Theme.secondaryHighlightColor
        visible: StorageJS.readSettingsValue("is_separated_messages") === 'true'
    }

    Row {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: Theme.paddingMedium
        anchors.leftMargin: Theme.paddingLarge
        anchors.rightMargin: Theme.paddingLarge
        spacing: Theme.paddingMedium

        Image {
            id: authorAvatar
            width: height
            height: Theme.itemSizeSmall - 2 * Theme.paddingSmall
            source: avatarSource
        }

        ContentItem {
            id: mainContent
            width: parent.width - authorAvatar.width - Theme.paddingMedium
            attachments: attachmentsData
            isOut: out === 1
            isRead: readState === 1
            content: textBody
            dateTime: datetime
            likes: likesCount
            reposts: repostsCount
            isLiked: isPostLiked
            isNews: isNewsContent
        }
    }
}
