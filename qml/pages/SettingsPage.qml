import QtQuick 2.0
import Sailfish.Silica 1.0

Page {

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: content.height

        Column {
            id: content
            width: parent.width

            PageHeader {
                title: qsTr("Settings")
            }

            TextSwitch {
                id: isOffile
                checked: settings.offlineStatus()
                text: qsTr("Be offline if possible")
                description: qsTr("Your status will be online only if you publish something on the wall or in the group.")

                onCheckedChanged: settings.setOfflineStatus(checked)
            }
        }
    }
}
