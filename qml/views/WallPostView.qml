import QtQuick 2.0
import Sailfish.Silica 1.0

Column {
    spacing: Theme.paddingLarge

    Label {
        width: parent.width
        wrapMode: Text.WordWrap
        text: _wallpost.text
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
    }

    Loader {
        property var rwallpost: _wallpost.repost
        width: parent.width - Theme.paddingSmall
        active: _repost !== 0
        source: "RepostView.qml"
    }
}

