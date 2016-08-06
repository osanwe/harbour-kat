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

#include "apirequest.h"

ApiRequest::ApiRequest(QObject *parent) : QObject(parent) {
    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
}

ApiRequest::~ApiRequest() {
    delete _manager;
}

void ApiRequest::makeApiGetRequest(QString method, QUrlQuery *query, TaskType type) {
    _currentTaskType = type;
    query->addQueryItem("access_token", _accessToken);
    query->addQueryItem("v", API_VERSION);
    QUrl url(API_URL + method);
    url.setQuery(query->query());
    qDebug() << url.toString();
    _manager->get(QNetworkRequest(url));
}

void ApiRequest::makePostRequest(QUrl url, QUrlQuery query, QByteArray body) {
    if (!query.isEmpty()) url.setQuery(query);
    _manager->post(QNetworkRequest(url), body);
}

void ApiRequest::setAccessToken(QString token) {
    _accessToken = token;
}

void ApiRequest::finished(QNetworkReply *reply) {
    QJsonDocument jDoc = QJsonDocument::fromJson(reply->readAll());
    QJsonValue jObj = jDoc.object().value("response");
    emit gotResponse(jObj, _currentTaskType);
    reply->deleteLater();
}
