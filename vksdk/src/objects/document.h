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

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QJsonObject>
#include <QObject>
#include <QString>

#include <QDebug>

class Document : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int ownerId READ ownerId CONSTANT)
    Q_PROPERTY(int size READ size CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString url READ url CONSTANT)
    Q_PROPERTY(QString photo READ photo CONSTANT)
    Q_PROPERTY(bool hasPhoto READ hasPhoto CONSTANT)

public:
    explicit Document(QObject *parent = 0);

    static Document* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    int ownerId() const;
    void setOwnerId(int ownerId);

    int size() const;
    void setSize(int size);

    QString title() const;
    void setTitle(const QString &title);

    QString url() const;
    void setUrl(const QString &url);

    bool hasPhoto() const;
    QString photo() const;
    void setPhoto100(const QString &photo100);
    void setPhoto130(const QString &photo130);

private:
    int _id;
    int _ownerId;
    int _size;
    QString _title;
    QString _url;
    QString _photo100;
    QString _photo130;
};

#endif // DOCUMENT_H
