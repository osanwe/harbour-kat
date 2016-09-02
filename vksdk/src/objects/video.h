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

#ifndef VIDEO_H
#define VIDEO_H

#include <QJsonObject>
#include <QObject>
#include <QString>

#include <QDebug>

class Video : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int ownerId READ ownerId CONSTANT)
    Q_PROPERTY(int duration READ duration CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString photo READ photo CONSTANT)
    Q_PROPERTY(QString video READ video CONSTANT)
    Q_PROPERTY(bool external READ external CONSTANT)

public:
    explicit Video(QObject *parent = 0);

    static Video* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    int ownerId() const;
    void setOwnerId(int ownerId);

    int duration() const;
    void setDuration(int duration);

    QString title() const;
    void setTitle(const QString &title);

    void setPhoto130(const QString &photo130);
    void setPhoto320(const QString &photo320);
    void setPhoto640(const QString &photo640);
    QString photo() const;

    void setMp4240(const QString &mp4240);
    void setMp4360(const QString &mp4360);
    void setMp4480(const QString &mp4480);
    void setMp4720(const QString &mp4720);
    void setExternal(const QString &external);
    QString video() const;

    bool external();

private:
    int _id;
    int _ownerId;
    int _duration;
    QString _title;
    QString _photo130;
    QString _photo320;
    QString _photo640;
    QString _mp4240;
    QString _mp4360;
    QString _mp4480;
    QString _mp4720;
    QString _external;
};

#endif // VIDEO_H
