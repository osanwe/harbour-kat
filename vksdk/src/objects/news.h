/*
  Copyright (C) 2016 Petr Vytovtov
  Contact: Petr Vytovtov <osanwe@protonmail.ch>
  All rights reserved.

  This file is part of Kat.

  Kat is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Kat is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Kat.  If not, see <http://www.gnu.org/licenses/>.
*/

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
#include "link.h"
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
    Q_PROPERTY(int commentsCount READ commentsCount CONSTANT)
    Q_PROPERTY(int likesCount READ likesCount CONSTANT)
    Q_PROPERTY(int repostsCount READ repostsCount CONSTANT)
    Q_PROPERTY(bool userLiked READ userLiked CONSTANT)
    Q_PROPERTY(bool userReposted READ userReposted CONSTANT)
    Q_PROPERTY(bool canComment READ canComment CONSTANT)
    Q_PROPERTY(QString text READ text CONSTANT)
    Q_PROPERTY(QString geoTile READ geoTile CONSTANT)
    Q_PROPERTY(QString geoMap READ geoMap CONSTANT)
    Q_PROPERTY(QVariant audios READ audios CONSTANT)
    Q_PROPERTY(QVariant documents READ documents CONSTANT)
    Q_PROPERTY(QVariant links READ links CONSTANT)
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
    void setText(QString text);

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

    QVariant links() const;
    QList<QObject *> linksList() const;
    void addLink(Link *link);

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

    int likesCount() const;
    void setLikesCount(int likesCount);

    int repostsCount() const;
    void setRepostsCount(int repostsCount);

    int commentsCount() const;
    void setCommentsCount(int commentsCount);

    bool userLiked() const;
    void setUserLiked(bool userLiked);

    bool userReposted() const;
    void setUserReposted(bool userReposted);

    bool canComment() const;
    void setCanComment(bool canComment);

private:
    int _id = 0;
    int _sourceId = 0;
    int _toId = 0;
    int _fromId = 0;
    int _date = 0;
    int _commentsCount = 0;
    int _likesCount = 0;
    int _repostsCount = 0;
    bool _userLiked;
    bool _userReposted;
    bool _canComment;
    QString _text;
    QString _geoTile;
    QString _geoMap;
    QList<QObject*> _audios;
    QList<QObject*> _documents;
    QList<QObject*> _links;
    QList<QObject*> _photos;
    QList<QObject*> _videos;
    QString _copyText;
    QJsonObject _repost;
};

#endif // NEWS_H
