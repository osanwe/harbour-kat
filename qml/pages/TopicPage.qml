import QtQuick 2.0
import Sailfish.Silica 1.0

Page {

    property int ownerId
    property int topicId
    property bool isClosed
    property string _title

    SilicaListView {
        id: topicMessagesList
        anchors.fill: parent
        anchors.bottomMargin: newCommentField.height
        clip: true

        header: PageHeader { title: _title }

        model: vksdk.commentsModel

        delegate: Item {
            width: parent.width
            height: childrenRect.height + Theme.paddingMedium

            Image {
                id: commentAvatar
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.topMargin: Theme.paddingSmall
                anchors.leftMargin: Theme.horizontalPageMargin
                width: Theme.iconSizeMedium
                height: Theme.iconSizeMedium
                source: avatarSource
            }

            Label {
                anchors.top: parent.top
                anchors.left: commentAvatar.right
                anchors.right: parent.right
                anchors.topMargin: Theme.paddingSmall
                anchors.leftMargin: Theme.paddingMedium
                anchors.rightMargin: Theme.horizontalPageMargin
                wrapMode: Text.WordWrap
                text: commentText
            }

            Component.onCompleted:
                if (index == vksdk.commentsModel.size-1)
                    vksdk.board.getComments(ownerId, topicId, vksdk.commentsModel.size)
        }

        VerticalScrollDecorator {}
    }

    TextField {
        id: newCommentField
        anchors.bottom: parent.bottom
        width: parent.width
        placeholderText: qsTr("Your comment")
        label: qsTr("Your comment")
        visible: !isClosed

        EnterKey.enabled: text.length > 0
        EnterKey.iconSource: "image://theme/icon-m-enter-accept"
        EnterKey.onClicked: {
            vksdk.board.createComment(ownerId, topicId, text)
            text = ""
        }
    }

    Connections {
        target: vksdk
        onCommentCreated: {
            vksdk.commentsModel.clear()
            vksdk.board.getComments(ownerId, topicId)
        }
    }

    Component.onCompleted: {
        vksdk.commentsModel.clear()
        vksdk.board.getComments(ownerId, topicId)
    }
}
