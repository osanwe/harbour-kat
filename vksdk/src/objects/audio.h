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
