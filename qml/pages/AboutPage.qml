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
    id: aboutPage

    SilicaListView {
        anchors.fill: parent

        model: ListModel {

            ListElement {
                aboutItemText: "Неофициальный клиент для самой популярной российской социальной сети, разрабатываемый силами <a href=\"https://udmlug.wordpress.com/\">Linux User Group Удмуртия</a> и распространяемый под лицензией GNU GPLv3."
            }

            ListElement {
                aboutItemText: "Со всеми возникающими вопросами, пожеланиями и предложениями можно обращаться по следующим ссылкам:"
            }

            ListElement {
                aboutItemText: "<a href=\"https://udmlug.wordpress.com/our-projects/vkfish/\">Страница проекта</a>"
            }

            ListElement {
                aboutItemText: "<a href=\"https://github.com/osanwe/vkFish\">GitHub</a>"
            }

            ListElement {
                aboutItemText: "<a href=\"https://twitter.com/Osanwe\">Ósanwe</a>"
            }

            ListElement {
                aboutItemText: "<a href=\"https://m.vk.com/nostariel\">Nostariel</a>"
            }

            ListElement {
                aboutItemText: "<a href=\"https://flattr.com/submit/auto?user_id=osanwe&url=https://vk.com/kat_sailfishos&title=Kat\">Поддержка</a>"
            }
        }

        header: PageHeader {
            title: "Kat v0.2.0-1436550333888"
        }

        delegate: Item {
            anchors.horizontalCenter: parent.horizontalCenter
            height: aboutItem.height + Theme.paddingMedium
            width: parent.width - Theme.paddingLarge * 2

            Label {
                id: aboutItem
                anchors.left: parent.left
                anchors.right: parent.right
                horizontalAlignment: index > 1 ? Text.AlignHCenter : Text.AlignLeft
                textFormat: Text.StyledText
                linkColor: Theme.highlightColor
                wrapMode: TextEdit.Wrap
                onLinkActivated: Qt.openUrlExternally(link)
                text: aboutItemText
            }
        }

        VerticalScrollDecorator {}
    }
}
