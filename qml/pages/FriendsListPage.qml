import QtQuick 2.0
import Sailfish.Silica 1.0

import "../views"

Page {
    id: friendsListPage

    property var userId
    property var type // 1 - all; 2 - online; 3 - mutual

    SilicaListView {
        id: friendsListView
        anchors.fill: parent

        header: PageHeader {
            title: type === 1 ? qsTr("Friends") : type === 2 ? qsTr("Online friends") :
                                                               qsTr("Mutual friends")
        }

        delegate: UserListItem {
            isUser: true
            avatarSource: model.modelData.photo50
            onlineStatus: model.modelData.online
            titleText: model.modelData.firstName + " " + modelData.lastName
            bodyText: model.modelData.status
        }

        VerticalScrollDecorator {}
    }

    Connections {
        target: vksdk
        onGotFriends: switch (type) {
                      case 1:
                          friendsListView.model = vksdk.getAllFriends()
                          break

                      case 2:
                          friendsListView.model = vksdk.getOnlineFriends()
                          break
                      }
    }

    Component.onCompleted: vksdk.friends.get(userId)
}

