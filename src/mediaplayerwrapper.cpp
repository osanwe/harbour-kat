#include "mediaplayerwrapper.h"

MediaPlayerWrapper::MediaPlayerWrapper(QObject *parent) : QObject(parent) {
    _player = new QMediaPlayer();
}

MediaPlayerWrapper::~MediaPlayerWrapper() {
    delete _player;
}

void MediaPlayerWrapper::playMedia(QString url) {
    _player->setMedia(QUrl(url));
    _player->play();
}

void MediaPlayerWrapper::pause() {
    _player->pause();
}

int MediaPlayerWrapper::position() const {
    return _player->position();
}

bool MediaPlayerWrapper::isPlaying() const {
    return _player->state() == QMediaPlayer::PlayingState;
}

