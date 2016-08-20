import QtQuick 2.0
import Sailfish.Silica 1.0
;import Sailfish.Media 1.0

Page {

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
        onShuffleClicked: {}
        onAddToPlaylist: {}
    }
}

