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

import "../emojione/emojione.js" as EmojiOne
import "../js/api/audios.js" as AudiosAPI
import "../js/api/videos.js" as VideosAPI


/*
  Common properties
    attachmentsData - the json object with info about attachments

  Messages properties
    isOut - the flag of incoming/outcoming messages; default - false
    isRead - "is message readed" flag; default - true

  Text properties
    content - the text for showing

  Images properties
    src - the URL to the image preview
    srcBig - the URL to the big image
    srcXBig - the URL to the extra big image
    srcXXBig - the URL to the extra-extra big image

  Videos properties
    vid - the id of the current video
    videoPreview - the URL to the image which is the video preview

  Audios properties
    oid - the id of the audio file owned
    aid - the id of the audio file
    artist - the artist of the audio
    title - the title of the audio

  Documents properties
    docName - the title of the document

  Datetime properties
    datetime - the string with the date and time of the current content
 */
Column {

    property variant attachments

    property bool isOut: false
    property bool isRead: true

    property string content

    property string src
    property string srcBig
    property string srcXBig
    property string srcXXBig

    property int vid
    property string videoPreview

    property int oid
    property int aid
    property string artist
    property string title

    property string docName

    property string dateTime

    Label {
        id: contentText
        width: parent.width
        horizontalAlignment: isOut ? Text.AlignRight : Text.AlignLeft
        text: EmojiOne.toImage(content)
        textFormat: Text.StyledText
        color: isRead ? Theme.primaryColor : Theme.highlightColor
        linkColor: readState ? Theme.secondaryColor : Theme.secondaryHighlightColor
        wrapMode: Text.Wrap
        maximumLineCount: 5

        onLinkActivated: Qt.openUrlExternally(link)
    }

    SilicaGridView {
        id: photosAttachment
        anchors.left: parent.left
        anchors.right: parent.right
        height: {
            var div = Math.floor(model.count / 4)
            if ((model.count % 4) != 0) div++
            return div * Theme.itemSizeMedium
        }
        clip: true
        layoutDirection: isOut ? Qt.RightToLeft: Qt.LeftToRight
        interactive: false
        cellWidth: Theme.itemSizeMedium
        cellHeight: Theme.itemSizeMedium

        model: ListModel {}

        delegate: Image {
            width: Theme.itemSizeMedium - Theme.paddingSmall
            height: Theme.itemSizeMedium - Theme.paddingSmall
            source: photo_75
            fillMode: Image.PreserveAspectCrop

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    var data
                    if (photo_2560) {
                        data = { "imageSource": photo_2560 }
                    } else if (photo_1280) {
                        data = { "imageSource": photo_1280 }
                    } else if (photo_807) {
                        data = { "imageSource": photo_807 }
                    } else if (photo_604) {
                        data = { "imageSource": photo_604 }
                    } else if (photo_130) {
                        data = { "imageSource": photo_130 }
                    } else {
                        data = { "imageSource": photo_75 }
                    }

                    pageContainer.push("../pages/ImagePage.qml", data)
                }
            }
        }
    }

    SilicaListView {
        id: videosAttachment
        anchors.left: parent.left
        anchors.right: parent.right
        height: model.count * Theme.itemSizeLarge * 2 + model.count * Theme.paddingMedium
        clip: true
        layoutDirection: isOut ? Qt.RightToLeft : Qt.LeftToRight
        spacing: Theme.paddingMedium
        interactive: false

        model: ListModel {}

        delegate: Image {
            anchors.left: parent.left
            anchors.right: parent.right
            height: Theme.itemSizeLarge * 2
            source: videoPreview
            fillMode: Image.PreserveAspectCrop

            Image {
                anchors.centerIn: parent
                source: "image://theme/icon-l-play"
            }

            MouseArea {
                anchors.fill: parent

                onClicked: VideosAPI.getVideo(vid)
            }
        }
    }

    SilicaListView {
        id: audiosAttachment
        anchors.left: parent.left
        anchors.right: parent.right
        height: model.count * (Theme.itemSizeMedium + Theme.paddingMedium)
        clip: true
        layoutDirection: isOut ? Qt.RightToLeft: Qt.LeftToRight
        spacing: Theme.paddingMedium
        interactive: false

        model: ListModel {}

        delegate: Item {
            anchors.left: parent.left
            anchors.right: parent.right
            height: Theme.itemSizeMedium

            property bool isPlaying: false

            Image {
                id: audioPlayPause
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: height
                source: isPlaying ? "image://theme/icon-l-pause" : "image://theme/icon-l-play"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (isPlaying) {
                            audioPlayer.pause()
                            isPlaying = false
                        } else {
                            audioPlayer.stop()
                            isPlaying = true
                            AudiosAPI.getAudio(oid, aid)
                        }
                    }
                }
            }

            Row {
                anchors.verticalCenter: audioPlayPause.verticalCenter
                anchors.left: audioPlayPause.right
                anchors.right: parent.right

                Label {
                    text: artist
                    font.bold: true
                }

                Label {
                    text: " - " + title
                }
            }
        }
    }

    SilicaListView {
        id: docsAttachment
        anchors.left: parent.left
        anchors.right: parent.right
        height: model.count * (Theme.itemSizeMedium + Theme.paddingMedium)
        clip: true
        layoutDirection: isOut ? Qt.RightToLeft : Qt.LeftToRight
        spacing: Theme.paddingMedium
        interactive: false

        model: ListModel {}

        delegate: BackgroundItem {
            anchors.left: parent.left
            anchors.right: parent.right
            height: Theme.itemSizeMedium

            Image {
                id: documentImage
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: height
                source: "image://theme/icon-l-document"
            }

            Label {
                anchors.verticalCenter: documentImage.verticalCenter
                anchors.left: documentImage.right
                anchors.right: parent.right
                text: docName
            }

            onClicked: {
                console.log("doc url = " + url)
                fileDownloader.startDownload(url, 1)
            }
        }
    }

    Label {
        id: datetimeText
        width: parent.width
        horizontalAlignment: isOut ? Text.AlignRight : Text.AlignLeft
        text: datetime
        font.pixelSize: Theme.fontSizeTiny
        color: isRead ? Theme.secondaryColor : Theme.secondaryHighlightColor
    }

    Component.onCompleted: {
        for (var index = 0; index < attachmentsData.count; index++) {
            if (attachmentsData.get(index).type) {
                switch (attachmentsData.get(index).type) {
                    case "photo": // photo from photo album
                        photosAttachment.model.append({ photo_75:   attachmentsData.get(index).photo.photo_75,
                                                        photo_130:  attachmentsData.get(index).photo.photo_130,
                                                        photo_604:  attachmentsData.get(index).photo.photo_604,
                                                        photo_807:  attachmentsData.get(index).photo.photo_807,
                                                        photo_1280: attachmentsData.get(index).photo.photo_1280,
                                                        photo_2560: attachmentsData.get(index).photo.photo_2560 })
                        break

                    case "posted_photo": // photo from user device
                        break

                    case "video": // videofile
                        videosAttachment.model.append({ vid:          attachmentsData.get(index).video.owner_id + "_" + attachmentsData.get(index).video.vid,
                                                        videoPreview: attachmentsData.get(index).video.image })
                        break

                    case "audio": // audiofile
                        audiosAttachment.model.append({ oid:    attachmentsData.get(index).audio.owner_id,
                                                        aid:    attachmentsData.get(index).audio.aid,
                                                        artist: attachmentsData.get(index).audio.artist,
                                                        title:  attachmentsData.get(index).audio.title })
                        break

                    case "doc": // document
                        docsAttachment.model.append({ docName: attachmentsData.get(index).doc.title,
                                                      url:     attachmentsData.get(index).doc.url })
                        break

                    case "graffiti": // graffiti
                        break

                    case "link": // link to web-page
                        break

                    case "note": // note
                        break

                    case "app": // image from app
                        break

                    case "poll": // poll
                        break

                    case "page": // wiki-page
                        break

                    case "album": // photo album
                        break

                    case "photos_list": // list of photos
                        break
                }
            } else {
                break
            }
        }
    }

}
