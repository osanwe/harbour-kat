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
            model: photos.length

            Image {
                width: calculateWidth(index)
                height: width * (sourceSize.height / sourceSize.width)
                fillMode: index === 0 ? Image.PreserveAspectFit : Image.PreserveAspectCrop
                source: photos[index].photoMaximum

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        var sources = []
                        var owners = []
                        var ids = []
                        for (var idx in photos) {
                            sources[idx] = photos[idx].photoMaximum
                            owners[idx] = photos[idx].ownerId
                            ids[idx] = photos[idx].id
                        }
                        pageStack.push(Qt.resolvedUrl("../pages/ImageViewPage.qml"), { current:     index,
                                                                                       imagesModel: sources,
                                                                                       ownerIds: owners,
                                                                                       photoIds: ids })
                    }
                }

                Component.onCompleted: console.log(index, photos)
            }
        }
    }

    function calculateWidth(index) {
        if (index === 0) return maximumWidth
        else {
            var otherPhotos = photos.length - 1
            if (otherPhotos % 4 == 0) {
                return maximumWidth / 4
            } else if (otherPhotos % 3 == 0) {
                return maximumWidth / 3
            } else if (otherPhotos % 2 == 0) {
                return maximumWidth / 2
            } else if (otherPhotos == 5) {
                if (index === 1 || index === 2) return maximumWidth / 2
                else return maximumWidth / 3
            } else if (otherPhotos == 7) {
                if (index === 1 || index === 2 || index === 3) return maximumWidth / 3
                else return maximumWidth / 4
            } else return maximumWidth
        }
    }
}

