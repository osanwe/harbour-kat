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

    property var model: [
        { aboutItemText: qsTr("Неофициальный клиент для самой популярной российской социальной сети, распространяемый под лицензией GNU GPLv3.") },
        { aboutItemText: qsTr("Со всеми возникающими вопросами, пожеланиями и предложениями можно обращаться по следующим ссылкам:") },
        { aboutItemText: "<a href=\"https://vk.com/kat_sailfishos\">" + qsTr("Страница проекта") + "</a>" },
        { aboutItemText: "<a href=\"https://github.com/osanwe/Kat\">" + qsTr("GitHub") + "</a>" },
        { aboutItemText: "<a href=\"https://flattr.com/submit/auto?user_id=osanwe&url=https://vk.com/kat_sailfishos&title=Kat\">" + qsTr("Поддержать проект") + "</a>" },
        { aboutItemText: "<a href=\"https://twitter.com/Osanwe\">" + qsTr("Ósanwe") + "</a>" },
        { aboutItemText: "<a href=\"https://m.vk.com/nostariel\">" + qsTr("Nostariel") + "</a>" },
        { aboutItemText: "<a href=\"https://github.com/ckazzku\">" + qsTr("Ckazzku") + "</a>" }
    ]

    SilicaListView {
        anchors.fill: parent

        model: aboutPage.model

        header: PageHeader {
            title: "Kat 0.1.7_1445791926"
        }

        delegate: Item {
            anchors.horizontalCenter: parent.horizontalCenter
            height: aboutItem.height + Theme.paddingMedium
            width: parent.width - Theme.paddingLarge * 2

            property var item: model.modelData ? model.modelData : model

            Label {
                id: aboutItem
                anchors.left: parent.left
                anchors.right: parent.right
                horizontalAlignment: index > 1 ? Text.AlignHCenter : Text.AlignLeft
                textFormat: Text.StyledText
                linkColor: Theme.highlightColor
                wrapMode: TextEdit.Wrap
                onLinkActivated: Qt.openUrlExternally(link)
                text: item.aboutItemText
            }
        }

        VerticalScrollDecorator {}
    }
}
