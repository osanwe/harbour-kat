#ifndef NEWS_H
#define NEWS_H

#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "audio.h"
#include "document.h"
#include "photo.h"
#include "video.h"

#include <QDebug>

class News : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int sourceId READ sourceId CONSTANT)
    Q_PROPERTY(int toId READ toId CONSTANT)
    Q_PROPERTY(int fromId READ fromId CONSTANT)
    Q_PROPERTY(int date READ date CONSTANT)
    Q_PROPERTY(QString text READ text CONSTANT)
    Q_PROPERTY(QString geoTile READ geoTile CONSTANT)
    Q_PROPERTY(QString geoMap READ geoMap CONSTANT)
    Q_PROPERTY(QVariant audios READ audios CONSTANT)
    Q_PROPERTY(QVariant documents READ documents CONSTANT)
    Q_PROPERTY(QVariant photos READ photos CONSTANT)
    Q_PROPERTY(QVariant videos READ videos CONSTANT)
    Q_PROPERTY(QString copyText READ copyText CONSTANT)
    Q_PROPERTY(News* repost READ repost CONSTANT)

public:
    explicit News(QObject *parent = 0);
    ~News();

    static News *fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    int sourceId() const;
    void setSourceId(int sourceId);

    int toId() const;
    void setToId(int toId);

    int fromId() const;
    void setFromId(int fromId);

    int date() const;
    void setDate(int date);

    QString text() const;
    void setText(const QString &text);

    QString geoTile() const;
    void setGeoTile(double lat, double lon);

    QString geoMap() const;
    void setGeoMap(double lat, double lon);

    QVariant audios() const;
    QList<QObject *> audiosList() const;
    void addAudio(Audio *audio);

    QVariant documents() const;
    QList<QObject *> documentsList() const;
    void addDocument(Document *document);

    QVariant photos() const;
    QList<QObject *> photosList() const;
    void addPhoto(Photo *photo);

    QVariant videos() const;
    QList<QObject *> videosList() const;
    void addVideo(Video *video);

    QString copyText() const;
    void setCopyText(const QString &copyText);

    News* repost() const;
    void setRepost(QJsonObject repost);

private:
    int _id = 0;
    int _sourceId = 0;
    int _toId = 0;
    int _fromId = 0;
    int _date = 0;
    QString _text;
    QString _geoTile;
    QString _geoMap;
    QList<QObject*> _audios;
    QList<QObject*> _documents;
    QList<QObject*> _photos;
    QList<QObject*> _videos;
    QString _copyText;
    QJsonObject _repost;
};

#endif // NEWS_H
