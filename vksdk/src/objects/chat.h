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

#ifndef CHAT_H
#define CHAT_H

#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QVariantList>

class Chat : public QObject
{
    Q_OBJECT
public:
    explicit Chat(QObject *parent = 0);

    static Chat* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    QString title() const;
    void setTitle(const QString &title);

    QString photo() const;
    void setPhoto(const QString &photo);

    QVariantList users() const;
    void setUsers(const QVariantList &users);

private:
    int _id;
    QString _title;
    QString _photo;
    QVariantList _users;
};

#endif // CHAT_H
