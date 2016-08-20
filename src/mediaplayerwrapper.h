#ifndef MEDIAPLAYERWRAPPER_H
#define MEDIAPLAYERWRAPPER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QUrl>

#include "vksdk/src/objects/audio.h"

#include <QDebug>

class MediaPlayerWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY stateChanged)
    Q_PROPERTY(int currentIndex READ currentIndex CONSTANT)
    Q_PROPERTY(int size READ size CONSTANT)
    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY mediaChanged)
    Q_PROPERTY(QString author READ author NOTIFY mediaChanged)
    Q_PROPERTY(QString title READ title NOTIFY mediaChanged)

public:
    explicit MediaPlayerWrapper(QObject *parent = 0);
    ~MediaPlayerWrapper();

//    Q_INVOKABLE void setPlaylist(QStringList urls, int index);
    Q_INVOKABLE void setPlaylist(QVariantList audios, int index);
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void next();
    Q_INVOKABLE void prev();
    Q_INVOKABLE void seekTo(int value);
    bool isPlaying() const;
    qint64 position();
    int currentIndex() const;
    int size() const;
    qint64 duration();
    QString author();
    QString title();

signals:
    void mediaChanged();
    void positionChanged(qint64 position);
    void stateChanged();

public slots:
    void _mediaChanged(QMediaContent content);
    void _positionChanged(qint64 pos);
    void _stateChanged(QMediaPlayer::State state);

private:
    QMediaPlayer *_player;
    QList<Audio*> _audios;
//    QMediaPlaylist *_playlist;
};

#endif // MEDIAPLAYERWRAPPER_H
