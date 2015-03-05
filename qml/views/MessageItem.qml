import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
//    width: parent.width
    height: messageText.height
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: { io === 1 ? 40 : 0 }
    anchors.rightMargin: { io === 1 ? 0 : 40 }

    TextArea {
        id: messageText
        width: parent.width
//        anchors.fill: parent
        verticalAlignment: { io === 1 ? TextEdit.AlignRight : TextEdit.AlignLeft }
        readOnly: true
        text: message
        color: { readState === 1 ? Theme.primaryColor : Theme.highlightColor }
        wrapMode: TextEdit.Wrap
    }
}
