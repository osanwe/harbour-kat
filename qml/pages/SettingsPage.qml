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
import "../js/storage.js" as StorageJS

Page {
    id: aboutPage

    SilicaFlickable {
        anchors.fill: parent

        Column {
            anchors.fill: parent

            PageHeader {
                title: "Настройки"
            }

            TextSwitch {
                text: "Отображать разделитель в сообщениях"
                checked: StorageJS.readSettingsValue("is_separated_messages") === 'true'

                onCheckedChanged: {
                    StorageJS.storeSettingsValue("is_separated_messages", checked)
                }
            }

            ComboBox {
                label: "Предпочитаемое качество видео"
                currentIndex: StorageJS.readSettingsValue("video_quality")

                menu: ContextMenu {
                    MenuItem { text: "720p" }
                    MenuItem { text: "480p" }
                    MenuItem { text: "360p" }
                    MenuItem { text: "240p" }

                    onActivated: {
                        StorageJS.storeSettingsValue("video_quality", index)
                    }
                }
            }
        }
    }
}
