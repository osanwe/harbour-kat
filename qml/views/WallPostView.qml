import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    spacing: Theme.paddingSmall

    Row {
        width: parent.width
        spacing: Theme.paddingSmall

        Label {
            width: parent.width - comments.width - likes.width - reposts.width - 3 * Theme.fontSizeTiny - 6 * Theme.paddingSmall
            color: Theme.secondaryColor
            font.pixelSize: Theme.fontSizeTiny
            text: convertUnixtimeToString(_wallpost.date)
        }

        Image {
            width: Theme.fontSizeTiny
            height: Theme.fontSizeTiny
            source: "image://theme/icon-s-chat"
        }

        Label {
            id: comments
            color: Theme.secondaryColor
            font.pixelSize: Theme.fontSizeTiny
            text: _wallpost.commentsCount
        }

        Image {
            width: Theme.fontSizeTiny
            height: Theme.fontSizeTiny
            source: "image://theme/icon-s-like?" +
                    (_wallpost.userLiked ? Theme.secondaryHighlightColor : Theme.secondaryColor)
        }

        Label {
            id: likes
            color: Theme.secondaryColor
            font.pixelSize: Theme.fontSizeTiny
            text: _wallpost.likesCount
        }

        Image {
            width: Theme.fontSizeTiny
            height: Theme.fontSizeTiny
            source: "image://theme/icon-s-retweet?" +
                    (_wallpost.userReposted ? Theme.secondaryHighlightColor : Theme.secondaryColor)
        }

        Label {
            id: reposts
            color: Theme.secondaryColor
            font.pixelSize: Theme.fontSizeTiny
            text: _wallpost.repostsCount
        }
    }

    Label {
        width: parent.width
        wrapMode: Text.WordWrap
        textFormat: Text.StyledText
        truncationMode: TruncationMode.Fade
        maximumLineCount: isFeed ? 5 : _wallpost.text.length
        text: _wallpost.text
        linkColor: Theme.highlightColor
        visible: _wallpost.text.length !== 0
    }

    AttachmentsView {
        id: attachments
        width: parent.width
        ageoTile: _wallpost.geoTile
        ageoMap: _wallpost.geoMap
        aphotos: _wallpost.photos
        avideos: _wallpost.videos
        aaudios: _wallpost.audios
        adocuments: _wallpost.documents
        alinks: _wallpost.links
    }

    Loader {
        property var rwallpost: _repost
        width: parent.width - Theme.paddingSmall
        active: _repost.id !== 0
        source: "RepostView.qml"
    }

    Component.onCompleted: console.log(_wallpost.repost.id)
}

