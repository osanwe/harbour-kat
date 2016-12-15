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

Page {
    id: imageViewPage

    property var imagesModel
    property var current

    SilicaListView {
        id: flick
        anchors.fill: parent
        anchors.bottomMargin: audioPlayer.open ? audioPlayer.height : 0
        clip: true
        snapMode: ListView.SnapOneItem
        orientation: ListView.HorizontalFlick
        highlightRangeMode: ListView.StrictlyEnforceRange
        cacheBuffer: width

        model: ListModel {}

        delegate: Item {
            width: flick.width
            height: flick.height
            clip: true

            Image {
                anchors.fill: parent
                sourceSize.height: window.height * 2
                fillMode: Image.PreserveAspectFit
                source: source_

                PinchArea {
                    anchors.fill: parent
                    pinch.target: parent
                    pinch.minimumScale: 1
                    pinch.maximumScale: 4
                }
            }
        }
    }

    Label {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: Theme.paddingLarge
        anchors.rightMargin: Theme.paddingLarge
        text: (flick.currentIndex + 1) + ' / ' + imagesModel.length
    }

//    onStatusChanged: if (status === PageStatus.Active) pageStack.pushAttached(Qt.resolvedUrl("AudioPlayerPage.qml"))

    Component.onCompleted: {
        for (var index in imagesModel) flick.model.append({ source_: imagesModel[index] })
        flick.currentIndex = current
    }
}

