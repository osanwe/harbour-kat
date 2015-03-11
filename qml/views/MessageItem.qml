import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem{
//    width: parent.width
    height: messageText.height
    anchors.left: parent.left
    anchors.right: parent.right
    highlighted: io === 0 & readState === 0

    Text {
        id: messageText
//        width: parent.width
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: { io === 1 ? 40 : 0 }
        anchors.rightMargin: { io === 1 ? 0 : 40 }
//        anchors.fill: parent
        verticalAlignment: { io === 1 ? TextEdit.AlignRight : TextEdit.AlignLeft }
//        readOnly: true
        text: message
        textFormat: Text.StyledText
        linkColor: { readState === 1 ? Theme.secondaryColor : Theme.secondaryHighlightColor }
        color: { readState === 1 ? Theme.primaryColor : Theme.highlightColor }
        wrapMode: TextEdit.Wrap

        onLinkActivated: Qt.openUrlExternally(link)
    }
}
