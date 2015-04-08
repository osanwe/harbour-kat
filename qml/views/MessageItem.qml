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

BackgroundItem {
    /*
     out
     readState
    */

    function calculateMessageItemHeight() {
        var textHeight = datetimeText.height + messageText.height + photosAttachment.height
        return Math.max(messageAvatar.height, textHeight) + 2 * Theme.paddingMedium
    }

    anchors.left: parent.left
    anchors.right: parent.right
    height: calculateMessageItemHeight()
    highlighted: out === 0 & readState === 0

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
            height: Theme.itemSizeSmall - 2 * Theme.paddingSmall
            width: height
            source: out === 0 ? avatarSource : userAvatar
        }

        Column {

            Label {
                id: messageText
                width: parent.parent.width - Theme.paddingMedium - messageAvatar.width
                horizontalAlignment: out === 1 ? Text.AlignRight : Text.AlignLeft
                text: message
                textFormat: Text.StyledText
                linkColor: readState === 1 ? Theme.secondaryColor : Theme.secondaryHighlightColor
                color: readState === 1 ? Theme.primaryColor : Theme.highlightColor
                wrapMode: Text.Wrap

                onLinkActivated: Qt.openUrlExternally(link)
            }

            SilicaGridView {
                id: photosAttachment
                anchors.left: parent.left
                anchors.right: parent.right
                height: contentHeight
                clip: true
                layoutDirection: out === 0 ? Qt.LeftToRight : Qt.RightToLeft

                model: ListModel {}

                delegate: BackgroundItem {
                    width: Theme.itemSizeMedium
                    height: Theme.itemSizeMedium

                    Image {
                        anchors.fill: parent
                        source: src
                        fillMode: Image.PreserveAspectCrop
                    }

                    onClicked: {
                        try {
                            var data = { "imageSource": srcXXBig }
                        } catch (e) {
                            try {
                                data = { "imageSource": srcXBig }
                            } catch (e) {
                                try {
                                    data = { "imageSource": srcBig }
                                } catch (e) {
                                    data = { "imageSource": src }
                                }
                            }
                        } finally {
                            pageContainer.push("../pages/ImagePage.qml", data)
                        }
                    }
                }
            }

//            SilicaListView {
//                id: attachmentsList
//
//                anchors.left: parent.left
//                anchors.right: parent.right
//                height: attachmentsData.count > 0 ? Theme.itemSizeSmall - 2 * Theme.paddingSmall : 0
//
//                spacing: 6
//                clip: true
//                orientation: ListView.Horizontal
//                layoutDirection: out == 0 ? Qt.LeftToRight : Qt.RightToLeft
//
//                model: attachmentsData
//
//                delegate: BackgroundItem {
//                    id: attachmentItem
//                    height: Theme.itemSizeSmall - 2 * Theme.paddingSmall
//                    width: height
//
//                    Image {
//                        id: contactAvatar
//                        anchors.fill: parent
//                        source: {
//                            console.log(attachmentsData.get(index).type + "")
//                            if (attachmentsData.get(index).type) {
//                                switch (attachmentsData.get(index).type) {
//                                    case "photo": return "image://theme/icon-l-image"
//                                    case "video": return "image://theme/icon-l-video"
//                                    case "audio": return "image://theme/icon-l-music"
//                                    case "doc": return "image://theme/icon-l-document"
//                                    case "wall": return "image://theme/icon-l-message"
//                                    case "point": return "image://theme/icon-l-gps"
//                                }
//                            } else {
//                                return "image://theme/icon-l-redirect"
//                            }
//                        }
//                    }
//
//                    onClicked: {
//                        if (attachmentsData.get(index).type) {
//                            switch (attachmentsData.get(index).type) {
//                                case "photo": {
//                                    var imageSrc = ""
//                                    if (attachmentsData.get(index).photo.src_xxbig) {
//                                        imageSrc = attachmentsData.get(index).photo.src_xxbig
//                                    } else if (attachmentsData.get(index).photo.src_xbig) {
//                                        imageSrc = attachmentsData.get(index).photo.src_xbig
//                                    } else if (attachmentsData.get(index).photo.src_big) {
//                                        imageSrc = attachmentsData.get(index).photo.src_big
//                                    } else {
//                                        imageSrc = attachmentsData.get(index).photo.src
//                                    }
//                                    pageContainer.push("../pages/ImagePage.qml",
//                                                       { "imageSource": imageSrc })
//                                    break;
//                                }
//                            }
//                        } else {
//                            //
//                        }
//                    }
//                }
//
//                HorizontalScrollDecorator {}
//            }

            Label {
                id: datetimeText
                width: parent.parent.width - Theme.paddingMedium - messageAvatar.width
                horizontalAlignment: out === 1 ? Text.AlignRight : Text.AlignLeft
                text: datetime
                font.pixelSize: Theme.fontSizeTiny
                color: readState === 1 ? Theme.secondaryColor : Theme.secondaryHighlightColor
            }
        }

    }

    Component.onCompleted: {
        for (var index = 0; index < attachmentsData.count; index++) {
            if (attachmentsData.get(index).type) {
                switch (attachmentsData.get(index).type) {
                    case "photo":
                        photosAttachment.model.append({ src:      attachmentsData.get(index).photo.src,
                                                        srcBig:   attachmentsData.get(index).photo.src_big,
                                                        srcXBig:  attachmentsData.get(index).photo.src_xbig,
                                                        srcXXBig: attachmentsData.get(index).photo.src_xxbig })
                        break
                    case "video": break
                    case "audio": break
                    case "doc": break
                    case "wall": break
                    case "point": break
                }
            } else {
                break
            }
        }
    }
}
