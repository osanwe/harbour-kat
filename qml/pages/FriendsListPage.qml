import QtQuick 2.0
import Sailfish.Silica 1.0

import "../views"

Page {
    id: friendsListPage

    property var userId
    property var type // 1 - all; 2 - online; 3 - mutual

    SilicaListView {
        anchors.fill: parent
        model: ListModel {}

        header: PageHeader {
            title: qsTr("Friends")
        }

        delegate: UserListItem {
            isUser: true
            avatarSource: ""
            onlineStatus: false
            titleText: ""
            bodyText: ""
        }
    }
}

