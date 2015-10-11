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

import "../views"
import "../emojione/emojione.js" as EmojiOne
import "../js/api/audios.js" as AudiosAPI
import "../js/api/videos.js" as VideosAPI
import "../js/storage.js" as StorageJS


BackgroundItem {
    /*
     out
     readState
     useSeparator
    */

    function calculateMessageItemHeight() {
//        var textHeight = datetimeText.height + messageText.height + photosAttachment.height +
//                videosAttachment.height + audiosAttachment.height + docsAttachment.height
        return Math.max(messageAvatar.height, mainContent.height) + 2 * Theme.paddingMedium
    }

    function buildMessageWithEmoji(message) {
        return EmojiOne.toImage(message)
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

    function playAudio(url) {
        audioPlayer.source = url
        audioPlayer.play()
    }

    Audio {
        id: audioPlayer
    }

    anchors.left: parent.left
    anchors.right: parent.right
    height: calculateMessageItemHeight()
    highlighted: out === 0 && readState === 0

    Separator {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: Theme.paddingMedium
        anchors.rightMargin: Theme.paddingMedium
        color: Theme.secondaryHighlightColor
        visible: useSeparator
    }

    Row {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: Theme.paddingMedium
        anchors.leftMargin: Theme.paddingLarge
        anchors.rightMargin: Theme.paddingLarge
        spacing: Theme.paddingMedium
        layoutDirection: out === 0 ? Qt.LeftToRight : Qt.RightToLeft

        Image {
            id: messageAvatar
            width: height
            height: Theme.itemSizeSmall - 2 * Theme.paddingSmall
            source: out === 0 ? avatarSource : userAvatar
        }

        ContentItem {
            id: mainContent
            width: parent.width - messageAvatar.width - Theme.paddingMedium
            attachments: attachmentsData
            isOut: out === 1
            isRead: readState === 1
            content: message
            dateTime: datetime
            isNews: isNewsContent
        }
    }
}
