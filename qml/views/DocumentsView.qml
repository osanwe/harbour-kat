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

    Column {
        width: parent.width

        Repeater {
            model: documents.length

            Item {
                width: maximumWidth
                height: childrenRect.height

                Loader {
                    active: documents[index].hasPhoto
                    sourceComponent: Component {

                        Image {
                            width: maximumWidth / 2
                            height: maximumWidth / 2
                            fillMode: Image.PreserveAspectFit
                            source: documents[index].photo

                            Rectangle {
                                anchors.bottom: parent.bottom
                                width: parent.width
                                height: childrenRect.height
                                color: "#7F000000"

                                Label {
                                    width: parent.width
                                    elide: Text.ElideMiddle
                                    text: documents[index].title
                                }
                            }
                        }
                    }
                }

                Loader {
                    active: !documents[index].hasPhoto
                    sourceComponent: Component {

                        Item {
                            width: maximumWidth
                            height: Theme.itemSizeMedium

                            Image {
                                id: docimage
                                anchors.left: parent.left
                                anchors.verticalCenter: parent.verticalCenter
                                width: Theme.iconSizeMedium
                                height: Theme.iconSizeMedium
                                source: "image://theme/icon-m-document"
                            }

                            Column {
                                anchors.left: docimage.right
                                anchors.right: parent.right
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.leftMargin: Theme.paddingMedium

                                Label {
                                    width: parent.width
                                    height: contentHeight
                                    elide: Text.ElideMiddle
                                    text: documents[index].title
                                }

                                Label {
                                    width: parent.width
                                    height: contentHeight
                                    truncationMode: TruncationMode.Fade
                                    text: documents[index].size
                                }
                            }
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: Qt.openUrlExternally(documents[index].url)
                }
            }
        }
    }
}

