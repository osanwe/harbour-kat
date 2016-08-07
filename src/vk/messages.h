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

#ifndef MESSAGES_H
#define MESSAGES_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include <QNetworkReply>
#include <QObject>
#include <QScopedPointer>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "apirequest.h"
#include "objects/chat.h"

#include <QDebug>

class Messages : public QObject
{
    Q_OBJECT

public:
    explicit Messages(QObject *parent = 0);
    ~Messages();

    void setAccessToken(QString value);

    Q_INVOKABLE void getChat(QStringList ids);
    Q_INVOKABLE void getDialogs(int offset = 0);
    Q_INVOKABLE void getHistory(int peerId, int offset = 0);

signals:
    void gotChatsList(QList<QObject*> chatsList);
    void gotDialogsList(QList<QObject*> dialogsList);
    void gotMessagesList(QList<QObject*> messagesList);

public slots:
    void gotResponse(QJsonValue value, ApiRequest::TaskType type);

private:
    QString _accessToken;
};

#endif // MESSAGES_H
