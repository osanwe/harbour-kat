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

import "../js/api/groups.js" as GroupsAPI
import "../js/api/wall.js" as WallAPI


Dialog {
    id: newMessageDialog

    property int groupId: 0
    property string deal: qsTr("На стену")

    property string attachmentsList: ""

    function addGroupToList(gid, gName) {
        searchGroupsList.model.append({ gid: gid,
                                        name: gName,
                                        isChoosen: false })
    }

    function clearChoosenItems() {
        var idx = 0
        while (idx < searchGroupsList.model.count) {
            searchGroupsList.model.set(idx, { isChoosen: false })
            idx++
        }
    }

    SilicaFlickable {
        anchors.fill: parent

        BusyIndicator {
            id: uploadingIndicator
            anchors.centerIn: parent
            size: BusyIndicatorSize.Large
            running: false
        }

        DialogHeader {
            id: newMessageHeader
            acceptText: deal
            cancelText: qsTr("Отменить")
        }

        SilicaListView {
            id: searchGroupsList
            anchors.fill: parent
            anchors.topMargin: newMessageHeader.height
            anchors.bottomMargin: newMessageText.height
            clip: true

            currentIndex: -1

            model: ListModel {
                Component.onCompleted: {
                    GroupsAPI.api_getModeredGroups()
                }
            }

            delegate: BackgroundItem {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: Theme.paddingLarge
                anchors.rightMargin: Theme.paddingLarge
                height: Theme.itemSizeSmall

                Row {
                    anchors.fill: parent
                    spacing: 6

                    Switch {
                        id: groupChoosenMode
                        height: groupName.height
                        width: height
                        automaticCheck: false
                        checked: isChoosen
                    }

                    Label {
                        id: groupName
                        width: parent.width - groupName.height - 6
                        truncationMode: TruncationMode.Fade
                        text: name
                    }
                }

                onClicked: {
                    clearChoosenItems()
                    if (deal === name) {
                        deal = qsTr("На стену")
                        groupId = 0
                    } else {
                        searchGroupsList.model.set(index, { isChoosen: true })
                        deal = name
                        groupId = gid
                    }
                }
            }
        }

        IconButton {
            id: attachmentsButton
            anchors.left: parent.left
            anchors.leftMargin: Theme.paddingLarge
            anchors.verticalCenter: newMessageText.verticalCenter
            width: Theme.iconSizeSmallPlus
            height: Theme.iconSizeSmallPlus
            icon.width: Theme.iconSizeSmallPlus
            icon.height: Theme.iconSizeSmallPlus
            icon.fillMode: Image.PreserveAspectFit
            icon.source: "image://theme/icon-m-attach"
        }

        Label {
            id: attachmentsCounter
            anchors.verticalCenter: attachmentsButton.top
            anchors.left: attachmentsButton.left
            anchors.leftMargin: text === "10" ? 0 : Theme.paddingSmall
            anchors.verticalCenterOffset: Theme.paddingSmall
            font.bold: true
            font.pixelSize: Theme.fontSizeTiny
            color: Theme.highlightColor
            text: {
                var attachmentsCount = attachmentsList.split(',').length - 1
                return attachmentsCount > 0 ? attachmentsCount : ""
            }
        }

        TextArea {
            id: newMessageText
            anchors.bottom: parent.bottom
            anchors.left: attachmentsButton.right
            anchors.right: parent.right
            placeholderText: qsTr("Сообщение:")
            label: qsTr("Сообщение")
        }

        PushUpMenu {

            MenuItem {
                text: qsTr("Attach image")
                onClicked: {
                    var imagePicker = pageStack.push("Sailfish.Pickers.ImagePickerPage")
                    imagePicker.selectedContentChanged.connect(function () {
                        uploadingIndicator.running = true
                        photos.attachImage(imagePicker.selectedContent, "WALL", groupId)
                    })
                }
            }
        }
    }

    Connections {
        target: photos
        onImageUploaded: {
            attachmentsList += imageName + ","
            uploadingIndicator.running = false
        }
    }

    onAccepted: {
        var messageText = encodeURIComponent(newMessageText.text)
        WallAPI.api_post(true, groupId, messageText, attachmentsList)
    }
}
