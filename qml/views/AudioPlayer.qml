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

DockedPanel {
    id: panel

    property var _audios
    property var _index

    function setAudios(audios, index) {
        _audios = audios;
        _index = index
    }

    width: parent.width
    height: Theme.itemSizeExtraLarge + Theme.paddingLarge
    dock: Dock.Bottom

    Item {
        anchors.fill: parent
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin
        anchors.topMargin: Theme.paddingLarge
        anchors.bottomMargin: Theme.paddingLarge

        Row {
            id: datacolumn
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            spacing: Theme.paddingMedium

            IconButton {
                width: Theme.iconSizeMedium
                height: Theme.iconSizeMedium
                icon.source: "image://theme/icon-m-left"
                onClicked: {
                    player.prev()
                    _index = player.currentIndex
                }
            }

            IconButton {
                width: Theme.iconSizeMedium
                height: Theme.iconSizeMedium
                icon.source: player.isPlaying ? "image://theme/icon-m-pause" : "image://theme/icon-m-play"
                onClicked: {
                    if (player.isPlaying) {
                        icon.source = "image://theme/icon-m-play"
                        player.pause()
                    } else {
                        icon.source = "image://theme/icon-m-pause"
                        player.pause()
                    }
                }
            }

            IconButton {
                width: Theme.iconSizeMedium
                height: Theme.iconSizeMedium
                icon.source: "image://theme/icon-m-right"
                onClicked: {
                    player.next()
                    _index = player.currentIndex
                }
            }

            Column {
                width: parent.width - 3 * Theme.iconSizeMedium - 3 * Theme.paddingMedium

                Label {
                    font.bold: true
                    truncationMode: TruncationMode.Fade
                    text: _audios.get(_index).title
                }

                Label {
                    truncationMode: TruncationMode.Fade
                    text: _audios.get(_index).artist
                }
            }
        }

        ProgressBar {
            id: dataduration
            anchors.centerIn: parent
            width: parent.width
            minimumValue: 0
            maximumValue: _audios.get(_index).duration
            valueText: "0:00"
            visible: false
        }

        Timer {

            property var counter: 4

            repeat: true
            running: panel.open
            onTriggered: {
                if (counter === 0) {
                    counter = 4
                    datacolumn.visible = !datacolumn.visible
                    dataduration.visible = !dataduration.visible
                }
                counter--
                var d = new Date(player.position)
                dataduration.value = player.position / 1000
                var seconds = d.getSeconds() > 10 ? d.getSeconds() : "0" + d.getSeconds()
                dataduration.valueText = d.getMinutes() + ":" + seconds
            }
        }
    }
}

