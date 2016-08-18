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

Item {
    width: maximumWidth
    height: childrenRect.height

    Flow {
        width: parent.width

        Repeater {
            model: videos.length

            Image {
                width: maximumWidth
                height: maximumWidth / 16 * 9
                fillMode: Image.PreserveAspectCrop
                source: videos[index].photo

                Image {
                    anchors.centerIn: parent
                    width: Theme.iconSizeMedium
                    height: Theme.iconSizeMedium
                    source: "image://theme/icon-m-play"
                }

                MouseArea {
                    anchors.fill: parent
//                    onClicked: vksdk.videos.get(videos[index].ownerId, videos[index].id)
                    onClicked: pageContainer.push(Qt.resolvedUrl("../pages/VideoPlayer.qml"),
                                                  { ownerId: videos[index].ownerId,
                                                    videoId: videos[index].id })
                }
            }
        }
    }
}

