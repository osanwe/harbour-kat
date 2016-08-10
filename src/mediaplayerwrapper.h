#ifndef MEDIAPLAYERWRAPPER_H
#define MEDIAPLAYERWRAPPER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QUrl>

#include <QDebug>

class MediaPlayerWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isPlaying READ isPlaying CONSTANT)
    Q_PROPERTY(int position READ position CONSTANT)
    Q_PROPERTY(int currentIndex READ currentIndex CONSTANT)

public:
    explicit MediaPlayerWrapper(QObject *parent = 0);
    ~MediaPlayerWrapper();

    Q_INVOKABLE void setPlaylist(QStringList urls, int index);
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void next();
    Q_INVOKABLE void prev();
    bool isPlaying() const;
    int position() const;
    int currentIndex() const;

private:
    QMediaPlayer *_player;
//    QMediaPlaylist *_playlist;
};

#endif // MEDIAPLAYERWRAPPER_H
