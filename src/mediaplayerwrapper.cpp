#include "mediaplayerwrapper.h"

MediaPlayerWrapper::MediaPlayerWrapper(QObject *parent) : QObject(parent) {
    _player = new QMediaPlayer();
    connect(_player, SIGNAL(positionChanged(qint64)), this, SLOT(_positionChanged(qint64)));
}

MediaPlayerWrapper::~MediaPlayerWrapper() {
    delete _player;
}

void MediaPlayerWrapper::setPlaylist(QStringList urls, int index) {
    QMediaPlaylist *_playlist = new QMediaPlaylist();
    foreach (QString url, urls) {
        _playlist->addMedia(QUrl(url));
    }
    _player->setPlaylist(_playlist);
    _playlist->setCurrentIndex(index);
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

void MediaPlayerWrapper::seekTo(int value)
{
    _player->setPosition(value * 1000);
}

qint64 MediaPlayerWrapper::position() {
    return _player->position();
}

int MediaPlayerWrapper::currentIndex() const {
    return _player->playlist()->currentIndex();
}

void MediaPlayerWrapper::_positionChanged(qint64 pos)
{
    emit positionChanged(pos);
}

bool MediaPlayerWrapper::isPlaying() const {
    return _player->state() == QMediaPlayer::PlayingState;
}

