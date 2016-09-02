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

#ifndef PHOTO_H
#define PHOTO_H

#include <QJsonObject>
#include <QObject>
#include <QString>

class Photo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString photoMinimum READ photoMinimum CONSTANT)
    Q_PROPERTY(QString photoMaximum READ photoMaximum CONSTANT)

public:
    explicit Photo(QObject *parent = 0);

    static Photo* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    int albumId() const;
    void setAlbumId(int albumId);

    int ownerId() const;
    void setOwnerId(int ownerId);

    int date() const;
    void setDate(int date);

    QString text() const;
    void setText(const QString &text);

    void setPhoto75(const QString &photo75);
    void setPhoto130(const QString &photo130);
    void setPhoto604(const QString &photo604);
    void setPhoto807(const QString &photo807);
    void setPhoto1280(const QString &photo1280);
    void setPhoto2560(const QString &photo2560);
    Q_INVOKABLE QString photoMinimum() const;
    Q_INVOKABLE QString photoMaximum() const;

private:
    int _id;
    int _albumId;
    int _ownerId;
    int _date;
    QString _text;
    QString _photo75;
    QString _photo130;
    QString _photo604;
    QString _photo807;
    QString _photo1280;
    QString _photo2560;
};

#endif // PHOTO_H
