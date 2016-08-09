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

Column {
    height: childrenRect.height
    spacing: Theme.paddingSmall

    property var aphotos
    property var avideos
    property var ageoTile
    property var ageoMap
    property var amessages

    Loader {
        property int maximumWidth: parent.width
        property var photos: aphotos
        active: aphotos.count > 0
        source: "PhotosView.qml"
    }

    Loader {
        property int maximumWidth: parent.width
        property var videos: avideos
        active: avideos.count > 0
        source: "VideosView.qml"
    }

    Loader {
        property int maximumWidth: parent.width
        property var geoTile: ageoTile
        property var geoMap: ageoMap
        active: typeof(ageoTile) !== 'undefined'
        source: "GeoItem.qml"
    }

    Loader {
        property int maximumWidth: parent.width
        property var messages: amessages
        active: amessages.count > 0
        source: "FwdMessages.qml"
    }
}

