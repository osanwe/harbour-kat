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

#include "users.h"

Users::Users(QObject *parent) : QObject(parent)
{}

Users::~Users()
{}

void Users::setApi(ApiRequest *api) {
    _api = api;
}

void Users::getSelfProfile() {
    getUserProfile(0);
}

void Users::getUserProfile(int id) {
    QUrlQuery *query = new QUrlQuery();
    if (id != 0) query->addQueryItem("user_ids", QString("%1").arg(id));
    query->addQueryItem("fields", "bdate,can_write_private_message,city,counters,online,photo_50,photo_200,photo_max_orig,relation,sex,status,verified");
    _api->makeApiGetRequest("users.get", query, ApiRequest::USERS_GET);
}

void Users::getUsersByIds(QStringList ids) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("user_ids", ids.join(","));
    query->addQueryItem("fields", "photo_50,online,status");
    _api->makeApiGetRequest("users.get", query, ApiRequest::USERS_GET_FRIENDS);
}

//void Users::gotResponse(QJsonValue value, ApiRequest::TaskType type) {
//    QJsonArray users;
//    switch (type) {
//    case ApiRequest::USERS_GET: {
//        users = value.toArray();
//        if (users.size() == 1) emit gotUserProfile(User::fromJsonObject(users.at(0).toObject()));
//        break;
//    }

//    case ApiRequest::USERS_GET_FRIENDS: {
//        users = value.toArray();
//        QList<QObject*> usersList;
//        for (int index = 0; index < users.size(); ++index) {
//            usersList.append(Friend::fromJsonObject(users.at(index).toObject()));
//        }
//        emit gotUsersList(usersList);
//        break;
//    }

//    default:
//        break;
//    }
//}

