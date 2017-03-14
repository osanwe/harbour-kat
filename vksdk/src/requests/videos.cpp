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

#include "videos.h"

Videos::Videos(QObject *parent) : QObject(parent)
{}

Videos::~Videos()
{}

void Videos::setApi(ApiRequest *api) {
    _api = api;
}

void Videos::get(int ownerId, int videoId) {
    QUrlQuery query;
    query.addQueryItem("owner_id", QString::number(ownerId));
    query.addQueryItem("videos", QString("%1_%2").arg(ownerId).arg(videoId));
    _api->makeApiGetRequest("video.get", query, ApiRequest::VIDEO_GET);
}

//void Videos::gotResponse(QJsonValue value, ApiRequest::TaskType type)
//{
//    switch (type) {
//    case ApiRequest::VIDEO_GET: {
//        QJsonArray items = value.toObject().value("items").toArray();
//        emit gotVideo(Video::fromJsonObject(items.at(0).toObject()));
//        break;
//    }

//    default:
//        break;
//    }
//}

