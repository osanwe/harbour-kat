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

#ifndef LINK_H
#define LINK_H

#include <QJsonObject>
#include <QObject>

class Link : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString url READ url CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)

public:
    explicit Link(QObject *parent = 0);

    static Link* fromJsonObject(QJsonObject object);

    QString url() const;
    void setUrl(const QString &url);

    QString title() const;
    void setTitle(const QString &title);

private:
    QString _url;
    QString _title;
};

#endif // LINK_H
