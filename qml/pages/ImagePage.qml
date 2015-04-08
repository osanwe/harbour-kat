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

Page {
    id: imagePage

    property string imageSource

    Image {
        id: showedImage
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        source: imageSource
    }

    MouseArea {
        anchors.fill: parent

        property bool doubleSize: false

        onDoubleClicked: {
            doubleSize = !doubleSize
            if (doubleSize) {
                showedImage.height *= 2
                showedImage.width *= 2
            } else {
                showedImage.height /= 2
                showedImage.width /= 2
            }
        }
    }
}
