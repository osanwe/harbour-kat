#include "mediaplayerwrapper.h"

MediaPlayerWrapper::MediaPlayerWrapper(QObject *parent) : QObject(parent) {
    _player = new QMediaPlayer();
}

MediaPlayerWrapper::~MediaPlayerWrapper() {
    delete _player;
}

void MediaPlayerWrapper::setPlaylist(QStringList urls, int index) {
    QMediaPlaylist *_playlist = new QMediaPlaylist();
    foreach (QString url, urls) {
        _playlist->addMedia(QUrl(url));
    }
    _playlist->setCurrentIndex(index);
    _player->setPlaylist(_playlist);
    _player->play();
}

void MediaPlayerWrapper::play() {
    _player->play();
}

void MediaPlayerWrapper::pause() {
    _player->pause();
}

void MediaPlayerWrapper::next() {
    _player->playlist()->next();
}

void MediaPlayerWrapper::prev() {
    _player->playlist()->previous();
}

int MediaPlayerWrapper::position() const {
    return _player->position();
}

int MediaPlayerWrapper::currentIndex() const {
    return _player->playlist()->currentIndex();
}

bool MediaPlayerWrapper::isPlaying() const {
    return _player->state() == QMediaPlayer::PlayingState;
}

