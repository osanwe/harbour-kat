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

#include "newsfeed.h"

Newsfeed::Newsfeed(QObject *parent) : QObject(parent)
{}

Newsfeed::~Newsfeed()
{}

void Newsfeed::setApi(ApiRequest *api) {
    _api = api;
}

void Newsfeed::get(QString startFrom) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("filters", "post");
    query->addQueryItem("return_banned", "0");
    query->addQueryItem("fields", "photo_50");
    if (!startFrom.isEmpty()) query->addQueryItem("start_from", startFrom);
    _api->makeApiGetRequest("newsfeed.get", query, ApiRequest::NEWSFEED_GET);
//    ApiRequest *request = new ApiRequest();
//    connect(request, SIGNAL(gotResponse(QJsonValue,ApiRequest::TaskType)),
//            this, SLOT(gotResponse(QJsonValue,ApiRequest::TaskType)));
//    request->setAccessToken(_accessToken);
//    request->makeApiGetRequest("newsfeed.get", query, ApiRequest::NEWSFEED_GET);
}

//void Newsfeed::gotResponse(QJsonValue value, ApiRequest::TaskType type) {
//    switch (type) {
//    case ApiRequest::NEWSFEED_GET: {
//        QJsonObject response = value.toObject();
//        QJsonArray _items = response.value("items").toArray();
//        QJsonArray _profiles = response.value("profiles").toArray();
//        QJsonArray _groups = response.value("groups").toArray();
//        QString _nextFrom = response.value("next_from").toString();
//        QList<News *> items;
//        QList<User *> profiles;
//        QList<Group *> groups;
//        for (int index = 0; index < _items.size(); ++index) {
//            items.append(News::fromJsonObject(_items.at(index).toObject()));
//        }
//        for (int index = 0; index < _profiles.size(); ++index) {
//            profiles.append(User::fromJsonObject(_profiles.at(index).toObject()));
//        }
//        for (int index = 0; index < _groups.size(); ++index) {
//            groups.append(Group::fromJsonObject(_groups.at(index).toObject()));
//        }
//        emit gotNewsfeed(items, profiles, groups, _nextFrom);
//    }

//    default:
//        break;
//    }
//}

