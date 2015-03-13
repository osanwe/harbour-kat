import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem{
    height: messageText.height + Theme.paddingMedium
    anchors.left: parent.left
    anchors.right: parent.right
    highlighted: io === 0 & readState === 0

    Label {
        id: messageText
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: io === 1 ? Theme.paddingLarge * 3 : Theme.paddingLarge
        anchors.rightMargin: io === 1 ? Theme.paddingLarge : Theme.paddingLarge * 3
        horizontalAlignment: io === 1 ? Text.AlignRight : Text.AlignLeft
        text: message
        textFormat: Text.StyledText
        linkColor: readState === 1 ? Theme.secondaryColor : Theme.secondaryHighlightColor
        color: readState === 1 ? Theme.primaryColor : Theme.highlightColor
        wrapMode: Text.Wrap

        onLinkActivated: Qt.openUrlExternally(link)
    }
}
