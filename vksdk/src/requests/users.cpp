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

Users::Users(QObject *parent) : RequestBase(parent)
{}

void Users::getSelfProfile() {
    getUserProfile(0);
}

void Users::getUserProfile(int id) {
    QUrlQuery query;
    if (id != 0) query.addQueryItem("user_ids", QString::number(id));
    query.addQueryItem("fields", "blacklisted,blacklisted_by_me,can_post,can_see_all_posts,"
                                  "can_see_audio,can_send_friend_request,can_write_private_message,"
                                  "domain,exports,friend_status,is_favorite,is_hidden_from_feed,"
                                  "photo_max_orig,verified,nickname,maiden_name,online,photo_50,"
                                  "photo_200,status,last_seen,bdate,relation,occupation,"
                                  "connections,counters,sex,city,country,home_town,contacts,site");
    _api->makeApiGetRequest("users.get", query, ApiRequest::USERS_GET);
}

void Users::getUsersByIds(const QStringList &ids) {
    QUrlQuery query;
    query.addQueryItem("user_ids", ids.join(","));
    query.addQueryItem("fields", "photo_50,online,status");
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

