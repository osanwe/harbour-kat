#ifndef AUDIO_H
#define AUDIO_H

#include <QJsonObject>
#include <QObject>
#include <QString>

class Audio : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int ownerId READ ownerId CONSTANT)
    Q_PROPERTY(int duration READ duration CONSTANT)
    Q_PROPERTY(QString artist READ artist CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString url READ url CONSTANT)

public:
    explicit Audio(QObject *parent = 0);

    static Audio* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    int ownerId() const;
    void setOwnerId(int ownerId);

    int duration() const;
    void setDuration(int duration);

    QString artist() const;
    void setArtist(const QString &artist);

    QString title() const;
    void setTitle(const QString &title);

    QString url() const;
    void setUrl(const QString &url);

private:
    int _id;
    int _ownerId;
    int _duration;
    QString _artist;
    QString _title;
    QString _url;
};

#endif // AUDIO_H
