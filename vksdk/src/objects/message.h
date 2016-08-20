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

#ifndef MESSAGE_H
#define MESSAGE_H

#include <math.h>

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QPair>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "audio.h"
#include "document.h"
#include "news.h"
#include "photo.h"
#include "video.h"

#include <QDebug>

class Message : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int userId READ userId CONSTANT)
    Q_PROPERTY(int chatId READ chatId CONSTANT)
    Q_PROPERTY(int fromId READ fromId CONSTANT)
    Q_PROPERTY(int date READ date CONSTANT)
    Q_PROPERTY(bool chat READ chat CONSTANT)
    Q_PROPERTY(bool readState READ readState CONSTANT)
    Q_PROPERTY(bool out READ out CONSTANT)
    Q_PROPERTY(QString body READ body CONSTANT)
    Q_PROPERTY(QString geoTile READ geoTile CONSTANT)
    Q_PROPERTY(QString geoMap READ geoMap CONSTANT)
    Q_PROPERTY(QVariant audios READ audios CONSTANT)
    Q_PROPERTY(QVariant documents READ documents CONSTANT)
    Q_PROPERTY(QVariant news READ news CONSTANT)
    Q_PROPERTY(QVariant photos READ photos CONSTANT)
    Q_PROPERTY(QVariant videos READ videos CONSTANT)
    Q_PROPERTY(QVariant fwdMessages READ fwdMessages CONSTANT)

public:
    explicit Message(QObject *parent = 0);

    static Message* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    int userId() const;
    void setUserId(int userId);

    int chatId() const;
    void setChatId(int chatId);

    int fromId() const;
    void setFromId(int fromId);

    int date() const;
    void setDate(int date);

    bool chat() const;
    void setChat(bool chat);

    bool readState() const;
    void setReadState(bool readState);

    bool out() const;
    void setOut(bool out);

    QString body() const;
    void setBody(const QString &body);

    QVariant photos() const;
    QList<QObject *> photosList() const;
    void addPhoto(Photo *photo);

    QVariant audios() const;
    QList<QObject *> audiosList() const;
    void addAudio(Audio *audio);

    QVariant documents() const;
    QList<QObject *> documentsList() const;
    void addDocument(Document *document);

    QVariant news() const;
    QList<QObject *> newsList() const;
    void addNews(News *news);

    QVariant videos() const;
    QList<QObject *> videosList() const;
    void addVideo(Video *video);

    QVariant fwdMessages() const;
    QList<QObject*> fwdMessagesList() const;
    void addFwdMessages(Message *message);

    QString geoTile() const;
    void setGeoTile(double lat, double lon);

    QString geoMap() const;
    void setGeoMap(double lat, double lon);

    bool hasAttachments() const;
    void setHasAttachments(bool hasAttachments);

private:
    int _id = 0;
    int _userId = 0;
    int _chatId = 0;
    int _fromId = 0;
    int _date = 0;
    bool _chat;
    bool _readState;
    bool _out;
    bool _hasAttachments = false;
    QString _body;
    QString _geoTile;
    QString _geoMap;
    QList<QObject*> _audios;
    QList<QObject*> _documents;
    QList<QObject*> _news;
    QList<QObject*> _photos;
    QList<QObject*> _videos;
    QList<QObject*> _fwdMessages;
};

#endif // MESSAGE_H
