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

ApplicationWindow
{
    id: application

    allowedOrientations: Orientation.All

    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    initialPage: {
        if (settings.accessToken()) {
            vksdk.setAccessTocken(settings.accessToken())
            vksdk.setUserId(settings.userId())
            return Qt.createComponent(Qt.resolvedUrl("pages/MainMenuPage.qml"))
        } else {
            return Qt.createComponent(Qt.resolvedUrl("pages/LoginPage.qml"))
        }
    }
}
