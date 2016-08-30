/*
  Copyright (C) 2016 Petr Vytovtov
                The element is got from Jolla Store client.
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
    id: morePanel

    property alias text: moreLabel.text
    property int horizontalMargin: Theme.horizontalPageMargin
    property alias busy: busyIndicator.running

    height: Theme.itemSizeSmall

    Label {
        id: moreLabel
        anchors {
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
            right: (morePanel.enabled || busy) ? moreImage.left : parent.right
            rightMargin: (morePanel.enabled || busy) ? Theme.paddingMedium : horizontalMargin
            verticalCenter: parent.verticalCenter
        }
        horizontalAlignment: Text.AlignRight
        truncationMode: TruncationMode.Fade
        color: (morePanel.highlighted || !morePanel.enabled)
               ? Theme.highlightColor
               : Theme.primaryColor
    }

    Image {
        id: moreImage
        anchors {
            right: parent.right
            rightMargin: horizontalMargin
            verticalCenter: parent.verticalCenter
        }
        visible: morePanel.enabled && !busy
        source: "image://theme/icon-m-right?"
                + (morePanel.highlighted ? Theme.highlightColor : Theme.primaryColor)
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: moreImage
        size: BusyIndicatorSize.Small
    }

    BoxBackground {
        anchors.fill: parent
        z: -1
    }
}
