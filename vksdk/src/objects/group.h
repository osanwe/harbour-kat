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

#ifndef GROUP_H
#define GROUP_H

#include <QJsonObject>
#include <QObject>
#include <QString>

#include <QDebug>

class Group : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString photo50 READ photo50 CONSTANT)
    Q_PROPERTY(QString photo100 READ photo100 CONSTANT)
    Q_PROPERTY(QString photo200 READ photo200 CONSTANT)

public:
    explicit Group(QObject *parent = 0);

    static Group* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString photo50() const;
    void setPhoto50(const QString &photo50);

    QString photo100() const;
    void setPhoto100(const QString &photo100);

    QString photo200() const;
    void setPhoto200(const QString &photo200);

    QString status() const;
    void setStatus(const QString &status);

private:
    int _id;
    QString _name;
    QString _status;
    QString _photo50;
    QString _photo100;
    QString _photo200;
};

#endif // GROUP_H
