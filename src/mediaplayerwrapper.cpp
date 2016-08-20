#include "mediaplayerwrapper.h"

MediaPlayerWrapper::MediaPlayerWrapper(QObject *parent) : QObject(parent) {
    _player = new QMediaPlayer(this);
    _model = new PlaylistModel(this);
    connect(_player, SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(_mediaChanged(QMediaContent)));
    connect(_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(_stateChanged(QMediaPlayer::State)));
    connect(_player, SIGNAL(positionChanged(qint64)), this, SLOT(_positionChanged(qint64)));
    qRegisterMetaType<PlaylistModel*>("PlaylistModel*");
}

MediaPlayerWrapper::~MediaPlayerWrapper() {
    delete _player;
    delete _model;
}

void MediaPlayerWrapper::setPlaylist(QVariantList audios, int index) {
    _audios.clear();
    QMediaPlaylist *_playlist = new QMediaPlaylist();
    foreach (QVariant audio, audios) {
        Audio *_audio = (Audio*)audio.value<QObject*>();
        _playlist->addMedia(QUrl(_audio->url()));
        _audios.append(_audio);
        _model->add(_audio);
    }
    _player->setPlaylist(_playlist);
    _playlist->setCurrentIndex(index);
    _model->setPlayingIndex(index);
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

void MediaPlayerWrapper::seekTo(int value) {
    _player->setPosition(value * 1000);
}

void MediaPlayerWrapper::jumpTo(int index) {
    _player->playlist()->setCurrentIndex(index);
}

qint64 MediaPlayerWrapper::position() {
    return _player->position();
}

int MediaPlayerWrapper::currentIndex() const {
    return _player->playlist()->currentIndex();
}

int MediaPlayerWrapper::size() const {
    return _audios.size();
}

qint64 MediaPlayerWrapper::duration() {
    if (_player->playlist()->isEmpty()) return 0;
    return _audios.at(_player->playlist()->currentIndex())->duration();
}

QString MediaPlayerWrapper::author() {
    if (_player->playlist()->isEmpty()) return "";
    return _audios.at(_player->playlist()->currentIndex())->artist();
}

QString MediaPlayerWrapper::title() {
    if (_player->playlist()->isEmpty()) return "";
    return _audios.at(_player->playlist()->currentIndex())->title();
}

void MediaPlayerWrapper::_mediaChanged(QMediaContent content) {
    emit mediaChanged();
}

void MediaPlayerWrapper::_positionChanged(qint64 pos) {
    emit positionChanged(pos);
}

void MediaPlayerWrapper::_stateChanged(QMediaPlayer::State state) {
    emit stateChanged();
}

PlaylistModel *MediaPlayerWrapper::model() const {
    return _model;
}

bool MediaPlayerWrapper::isPlaying() const {
    return _player->state() == QMediaPlayer::PlayingState;
}

