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

#include "messages.h"

Messages::Messages(QObject *parent) : QObject(parent) {}

Messages::~Messages() {}

void Messages::setAccessToken(QString value) {
    _accessToken = value;
}

void Messages::getChat(QStringList ids) {
    QUrlQuery *query = new QUrlQuery();
    if (ids.size() == 1) query->addQueryItem("chat_id", ids.at(0));
    else if (ids.size() > 1) query->addQueryItem("chat_ids", ids.join(","));
    ApiRequest *request = new ApiRequest(this);
    connect(request, SIGNAL(gotResponse(QJsonObject,ApiRequest::TaskType)),
            this, SLOT(gotResponse(QJsonObject,ApiRequest::TaskType)));
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("messages.getChat", new QUrlQuery(), ApiRequest::MESSAGES_GET_CHAT);
}

void Messages::getDialogs(int offset) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("offset", QString("%1").arg(offset));
    ApiRequest *request = new ApiRequest(this);
    connect(request, SIGNAL(gotResponse(QJsonObject,ApiRequest::TaskType)),
            this, SLOT(gotResponse(QJsonObject,ApiRequest::TaskType)));
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("messages.getDialogs", query, ApiRequest::MESSAGES_GET_DIALOGS);
}

void Messages::gotResponse(QJsonValue value, ApiRequest::TaskType type) {
//    switch (type) {
//    case ApiRequest::MESSAGES_GET_CHAT:
//        QJsonArray chats = value.toArray();
//        QList<QObject*> chatsList;
//        for (int index = 0; index < chats.size(); ++index) {
////            chatsList.append(Chat::fromJsonObject(chats.at(index).toObject()));
//        }
//        emit gotChatsList(chatsList);
//        break;

//    case ApiRequest::MESSAGES_GET_DIALOGS:
//        QJsonArray dialogs = value.toObject().value("items").toArray();
//        QList<QObject*> dialogsList;
//        for (int index = 0; index < dialogs.size(); ++index) {
//            dialogsList.append(Dialog::fromJsonObject(dialogs.at(index).toObject()));
//        }
//        emit gotDialogsList(dialogsList);
//        break;
//    }
}

