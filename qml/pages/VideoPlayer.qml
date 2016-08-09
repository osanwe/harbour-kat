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
import QtMultimedia 5.0
import Sailfish.Silica 1.0

Page {
    anchors.fill: parent

    property var url
    property var duration

    property bool isPlaying: true

    allowedOrientations: Orientation.LandscapeMask

    Video {
        id: videoView
        anchors.fill: parent
        autoPlay: true
        fillMode: VideoOutput.PreserveAspectFit
        source: url

        MouseArea {
            anchors.fill: parent
            onClicked: {
                playPauseButton.visible = !playPauseButton.visible
                videoProgressBar.visible = !videoProgressBar.visible
            }
        }
    }

    Image {
        id: playPauseButton
        anchors.centerIn: parent
        visible: false
        source: isPlaying ? "image://theme/icon-l-pause" : "image://theme/icon-l-play"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (isPlaying) {
                    videoView.pause()
                    isPlaying = false
                } else {
                    videoView.play()
                    isPlaying = true
                }
            }
        }
    }

    ProgressBar {
        id: videoProgressBar
        anchors.bottom: parent.bottom
        width: parent.width
        maximumValue: duration
        value: videoView.position / 1000
        visible: false
    }

    Component.onCompleted: console.log(url)
}
