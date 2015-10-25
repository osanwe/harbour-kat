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
import "../js/types.js" as TypesJS

Page {
    id: aboutPage

    SilicaFlickable {
        anchors.fill: parent

        Column {
            anchors.fill: parent
            spacing: Theme.paddingMedium

            PageHeader {
                title: qsTr("Настройки")
            }

            ComboBox {
                label: qsTr("Стартовая страница")
                currentIndex: StorageJS.readSettingsValue("start_page")

                menu: ContextMenu {
                    MenuItem { text: qsTr("Новости") }
                    MenuItem { text: qsTr("Сообщения") }

                    onActivated: StorageJS.storeSettingsValue("start_page", index)
                }
            }

            ComboBox {
                label: qsTr("Создать с обложки")
                currentIndex: StorageJS.readSettingsValue("create_from_cover")

                menu: ContextMenu {
                    MenuItem { text: qsTr("Сообщение") }
                    MenuItem { text: qsTr("Запись на стене") }

                    onActivated: StorageJS.storeSettingsValue("create_from_cover", index)
                }
            }

            ComboBox {
                label: qsTr("Предпочитаемое качество видео")
                currentIndex: StorageJS.readSettingsValue("video_quality")

                menu: ContextMenu {
                    MenuItem { text: "720p" }
                    MenuItem { text: "480p" }
                    MenuItem { text: "360p" }
                    MenuItem { text: "240p" }

                    onActivated: StorageJS.storeSettingsValue("video_quality", index)
                }
            }

            ComboBox {
                label: qsTr("Обновление сообщений")
                currentIndex: StorageJS.readSettingsValue("update_interval", 3)

                menu: ContextMenu {
                    MenuItem { text: TypesJS.UpdateInterval.items[0].name }
                    MenuItem { text: TypesJS.UpdateInterval.items[1].name }
                    MenuItem { text: TypesJS.UpdateInterval.items[2].name }
                    MenuItem { text: TypesJS.UpdateInterval.items[3].name }

                    onActivated: StorageJS.storeSettingsValue("update_interval", index)
                }
            }

            TextSwitch {
                text: qsTr("Обновлять сообщения вручную")
                checked: StorageJS.readSettingsValue("update_manual", false) === 'true'

                onCheckedChanged: StorageJS.storeSettingsValue("update_manual", checked)
            }

            TextSwitch {
                text: qsTr("По возможности быть offline")
                checked: StorageJS.readSettingsValue("is_offline_mode") === 'true'

                onCheckedChanged: StorageJS.storeSettingsValue("is_offline_mode", checked)
            }

            TextSwitch {
                text: qsTr("Отображать разделитель в сообщениях")
                checked: StorageJS.readSettingsValue("is_separated_messages") === 'true'

                onCheckedChanged: StorageJS.storeSettingsValue("is_separated_messages", checked)
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width / 3 * 2
                text: qsTr("Очистить кэш")

                onClicked: {
                    console.log(storage.clearCache())
                    console.log(fileDownloader.clearCache())
                }
            }
        }
    }
}
