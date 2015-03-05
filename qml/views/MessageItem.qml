import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    width: parent.width
    height: messageText.height

    TextArea {
        id: messageText
        width: parent.width
        anchors.fill: parent
        readOnly: true
        text: message
        wrapMode: TextEdit.WordWrap
    }
}
