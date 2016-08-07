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

    QVariant fwdMessages() const;
    void addFwdMessages(Message *message);

    QString geoTile() const;
    void setGeoTile(double lat, double lon);

    QString geoMap() const;
    void setGeoMap(double lat, double lon);

private:
    int _id;
    int _userId;
    int _chatId;
    int _fromId;
    int _date;
    bool _chat;
    bool _readState;
    bool _out;
    QString _body;
    QString _geoTile;
    QString _geoMap;
    // Attachments
    QList<QObject*> _fwdMessages;
};

#endif // MESSAGE_H
