#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>
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

#include <QUrl>
#include <QUrlQuery>
#include <QVariant>

#include "objects/dialog.h"
#include "objects/message.h"

#include <QDebug>

class ApiRequest : public QObject
{
    Q_OBJECT

public:
    explicit ApiRequest(QObject *parent = 0);
    ~ApiRequest();

    enum TaskType {
        FRIENDS_GET,
        FRIENDS_GET_MUTUAL,
        FRIENDS_GET_ONLINE,
        LIKES_ADD,
        MESSAGES_GET_CHAT,
        MESSAGES_GET_DIALOGS,
        MESSAGES_GET_HISTORY,
        MESSAGES_SEND,
        NEWSFEED_GET,
        PHOTOS_GET_MESSAGES_UPLOAD_SERVER,
        PHOTOS_GET_WALL_UPLOAD_SERVER,
        PHOTOS_SAVE_MESSAGES_PHOTO,
        PHOTOS_SAVE_WALL_PHOTO,
        USERS_GET,
        USERS_GET_FRIENDS,
        VIDEO_GET,
        WALL_GET_BY_ID,
    };

    void makeApiGetRequest(QString method, QUrlQuery *query, TaskType type);
    void makePostRequest(QUrl url, QUrlQuery query, QByteArray body);

    void setAccessToken(QString token);

signals:
    void gotResponse(QJsonValue value, ApiRequest::TaskType type);

public slots:
    void finished(QNetworkReply *reply);

private:
    const QString API_URL = "https://api.vk.com/method/";
    const QString API_VERSION = "5.53";

    QString _accessToken;
    TaskType _currentTaskType;

    QNetworkAccessManager *_manager;
};

#endif // APIREQUEST_H
