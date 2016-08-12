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

#ifndef USERS_H
#define USERS_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QString>
#include <QUrlQuery>

#include "apirequest.h"
#include "objects/friend.h"
#include "objects/user.h"

#include <QDebug>

class Users : public QObject
{
    Q_OBJECT
public:
    explicit Users(QObject *parent = 0);
    ~Users();

    void setAccessToken(QString value);

    Q_INVOKABLE void getSelfProfile();
    Q_INVOKABLE void getUserProfile(int id);
    Q_INVOKABLE void get(QStringList ids);

signals:
    void gotUserProfile(User *user);
    void gotUsersList(QList<QObject*> usersList);

public slots:
    void gotResponse(QJsonValue value, ApiRequest::TaskType type);

private:
    QString _accessToken;
};

#endif // USERS_H
