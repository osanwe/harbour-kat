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

#include <QHttpMultiPart>
#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>

//#include "objects/dialog.h"
//#include "objects/message.h"

#include <QDebug>

class ApiRequest : public QObject
{
    Q_OBJECT

public:
    explicit ApiRequest(QObject *parent = 0);
    ~ApiRequest();

    enum TaskType {
        ACCOUNT_BAN_USER,
        ACCOUNT_GET_COUNTERS,
        ACCOUNT_SET_ONLINE,
        ACCOUNT_UNBAN_USER,
        AUDIO_ADD,
        AUDIO_GET,
        AUDIO_SEARCH,
        FRIENDS_GET,
        FRIENDS_GET_MUTUAL,
        FRIENDS_GET_ONLINE,
        GROUPS_GET,
        GROUPS_GET_BY_ID,
        LIKES_ADD,
        MESSAGES_GET_BY_ID,
        MESSAGES_GET_CHAT,
        MESSAGES_GET_DIALOGS,
        MESSAGES_GET_HISTORY,
        MESSAGES_MARK_AS_READ,
        MESSAGES_SEND,
        MESSAGES_SET_ACTIVITY,
        NEWSFEED_GET,
        PHOTOS_GET_MESSAGES_UPLOAD_SERVER,
        PHOTOS_GET_WALL_UPLOAD_SERVER,
        PHOTOS_SAVE_MESSAGES_PHOTO,
        PHOTOS_SAVE_WALL_PHOTO,
        PHOTOS_UPLOAD_TO_SERVER,
        STATS_GET,
        STATS_TRACK_VISITOR,
        USERS_GET,
        USERS_GET_FRIENDS,
        VIDEO_GET,
        WALL_CREATE_COMMENT,
        WALL_GET,
        WALL_GET_BY_ID,
        WALL_GET_COMMENTS,
        WALL_REPOST,
    };

    void makeApiGetRequest(QString method, QUrlQuery *query, TaskType type);
    void makePostRequest(QUrl url, QUrlQuery *query, QHttpMultiPart *multipart, TaskType type);

    void setAccessToken(QString token);

signals:
    void gotResponse(QJsonValue value, ApiRequest::TaskType type);

public slots:
    void finished(QNetworkReply *reply);

private:
    const QString API_URL = "https://api.vk.com/method/";
    const QString API_VERSION = "5.60";

    QString _accessToken;
    QHash<QString, TaskType> _history;

    QNetworkAccessManager *_manager;
};

#endif // APIREQUEST_H
