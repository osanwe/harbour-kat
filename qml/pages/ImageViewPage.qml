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

    property var photoSource

    SilicaFlickable {
        id: flick
        anchors.fill: parent
        contentWidth: window.width
        contentHeight: window.height
        clip: true

        PinchArea {

            property real initialWidth
            property real initialHeight

            width: Math.max(flick.contentWidth, flick.width)
            height: Math.max(flick.contentHeight, flick.height)

            Rectangle {
                width: flick.contentWidth
                height: flick.contentHeight
                color: "#00000000"

                Image {
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: photoSource

                    MouseArea {
                        anchors.fill: parent

                        onDoubleClicked: {
                            flick.contentWidth = window.width
                            flick.contentHeight = window.height
                        }
                    }
                }
            }

            onPinchStarted: {
                initialWidth = flick.contentWidth
                initialHeight = flick.contentHeight
            }

            onPinchUpdated: {
                flick.contentX += pinch.previousCenter.x - pinch.center.x
                flick.contentY += pinch.previousCenter.y - pinch.center.y
                flick.resizeContent(Math.max(window.width, initialWidth * pinch.scale),
                                    Math.max(window.height, initialHeight * pinch.scale),
                                    pinch.center)
            }

            onPinchFinished: flick.returnToBounds()
        }
    }
}

