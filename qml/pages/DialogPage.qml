import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: dialogPage

    property string fullname

    SilicaFlickable {
        anchors.fill: parent

        PageHeader { title: fullname }

        TextArea {
            id: messageInput
            width: parent.width
            anchors.bottom: parent.bottom
            placeholderText: "Сообщение:"
            label: "Сообщение:"
        }
    }
}
