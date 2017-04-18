import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {

    property string type: "wall"
    property int sourceId: 0
    property int postId: 0

    DialogHeader {
        id: header
        acceptText: qsTr("Share")
        cancelText: qsTr("Cancel")
    }

    SilicaFlickable {
        id: flick
        anchors.fill: parent
        anchors.topMargin: header.height
        clip: true

        TextArea {
            id: repostComment
            anchors.fill: parent
        }
    }

    onAccepted: {
        vksdk.wall.repost(type, sourceId, postId, repostComment.text)
    }
}
