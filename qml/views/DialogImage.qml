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

Item {
    property var src

    function calculateWidth(counter, parentWidth) {
        switch (src.length) {
        case 1:
            if (counter === 1) return parentWidth
            else return 0

        case 2:
            if (counter === 1 || counter === 2) return parentWidth / 2
            else return 0

        case 3:
            if (counter === 1 || counter === 2 || counter === 3) return parentWidth / 2
            else return 0

        default:
            return parentWidth / 2
        }
    }

    function calculateHeight(counter, parentHeight) {
        switch (src.length) {
        case 1:
            if (counter === 1) return parentHeight
            else return 0

        case 2:
            if (counter === 1 || counter === 2) return parentHeight
            else return 0

        case 3:
            if (counter === 1 || counter === 2 || counter === 3) return parentHeight / 2
            else return 0

        default:
            return parentHeight / 2
        }
    }

    Grid {
        anchors.fill: parent
        columns: 2
        rows: 2

        Image {
            width: calculateWidth(1, parent.width)
            height: calculateHeight(1, parent.height)
            source: src[0]
        }

        Image {
            width: calculateWidth(2, parent.width)
            height: calculateHeight(2, parent.height)
            source: src.length >= 2 ? src[1] : ""
        }

        Image {
            width: calculateWidth(2, parent.width)
            height: calculateHeight(2, parent.height)
            source: src.length >= 3 ? src[2] : ""
        }

        Image {
            width: calculateWidth(2, parent.width)
            height: calculateHeight(2, parent.height)
            source: src.length >= 4 ? src[3] : ""
        }
    }
}
