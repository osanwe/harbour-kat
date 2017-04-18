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
    query->addQueryItem("access_token", _accessToken);
    query->addQueryItem("v", API_VERSION);
    QUrl url(API_URL + method);
    url.setQuery(query->query());
    _history[url.toString()] = type;
    qDebug() << url;
    _manager->get(QNetworkRequest(url));
}

void ApiRequest::makePostRequest(QUrl url, QUrlQuery *query, QHttpMultiPart *multipart, TaskType type) {
    if (!query->isEmpty()) url.setQuery(query->query());
    _history[url.toString()] = type;
    _manager->post(QNetworkRequest(url), multipart);
}

void ApiRequest::setAccessToken(QString token) {
    _accessToken = token;
}

void ApiRequest::finished(QNetworkReply *reply) {
    QString requestedUrl = reply->url().toString();
    if (_history.contains(requestedUrl)) {
        QJsonDocument jDoc = QJsonDocument::fromJson(reply->readAll());
        qDebug() << jDoc;
        QJsonObject jObj = jDoc.object();
        if (_history[requestedUrl] == PHOTOS_UPLOAD_TO_SERVER) {
            emit gotResponse(jObj, _history[requestedUrl]);
        } else if (jObj.contains("response")) {
            QJsonValue jVal = jObj.value("response");
            emit gotResponse(jVal, _history[requestedUrl]);
        } else if (jObj.contains("error")) {
            qDebug() << "Error in API request!";
        }
        _history.remove(requestedUrl);
    }
    reply->deleteLater();
}
