import QtQuick 2.0
import Sailfish.Silica 1.0
;import Sailfish.Media 1.0

Page {

    SilicaListView {
        id: playlist
        anchors.fill: parent
        anchors.bottomMargin: audioPlayer.height
        clip: true
        model: player.model
        header: PageHeader {
            title: qsTr("Audios")
        }
        delegate: MediaListItem {
            width: parent.width
            height: childrenRect.height

            duration: _duration
            title: _title
            subtitle: _subtitle
            playing: _playing

            onClicked: player.jumpTo(index)
        }

        PullDownMenu {

            MenuItem {
                text: qsTr("My audios")
                onClicked: vksdk.audios.get()
            }
        }

        VerticalScrollDecorator {}
    }

    MediaPlayerControlsPanel {
        id: audioPlayer
        active: true
        open: true
        playing: player.isPlaying
        author: player.author
        title: player.title
        duration: player.duration
        position: player.position / 1000

        onPlayPauseClicked: {
            if (playing) player.pause()
            else player.play()
        }
        onPreviousClicked: if (player.currentIndex > 0) player.prev()
        onNextClicked: if (player.currentIndex < player.size-1) player.next()
        onSliderReleased: player.seekTo(value)
        onRepeatClicked: {}
        onShuffleClicked: {
            player.shuffle = !player.shuffle
            shuffle = player.shuffle ? MediaPlayerControls.ShuffleTracks :
                                       MediaPlayerControls.NoShuffle
        }
        onAddToPlaylist: {}
    }

    Connections {
        target: player
        onMediaChanged: {
            player.model.setPlayingIndex(player.currentIndex);
        }
    }

    Connections {
        target: vksdk
        onGotUserAudios: {
//            console.log(audios.length)
            player.setPlaylist(audios, -1)
        }
    }
}

