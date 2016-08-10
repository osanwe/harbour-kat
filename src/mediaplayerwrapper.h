#ifndef MEDIAPLAYERWRAPPER_H
#define MEDIAPLAYERWRAPPER_H

#include <QMediaPlayer>
#include <QObject>
#include <QString>
#include <QUrl>

#include <QDebug>

class MediaPlayerWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isPlaying READ isPlaying CONSTANT)
    Q_PROPERTY(int position READ position CONSTANT)

public:
    explicit MediaPlayerWrapper(QObject *parent = 0);
    ~MediaPlayerWrapper();

    Q_INVOKABLE void playMedia(QString url);
    Q_INVOKABLE void pause();
    bool isPlaying() const;
    int position() const;

private:
    QMediaPlayer *_player;
};

#endif // MEDIAPLAYERWRAPPER_H
