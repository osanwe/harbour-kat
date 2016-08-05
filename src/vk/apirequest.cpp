#include "apirequest.h"

ApiRequest::ApiRequest(QObject *parent) : QObject(parent) {
    _manager = new QNetworkAccessManager(this);
}

ApiRequest::~ApiRequest() {
    delete _manager;
}

void ApiRequest::makeGetRequest(QUrl url, QUrlQuery query) {
    if (!query.isEmpty()) url.setQuery(query);
    _manager->get(QNetworkRequest(url));
}

void ApiRequest::makePostRequest(QUrl url, QUrlQuery query, QByteArray body) {
    if (!query.isEmpty()) url.setQuery(query);
    _manager->post(QNetworkRequest(url), body);
}

void ApiRequest::finished(QNetworkReply *reply) {
    qDebug() << reply->readAll();
    reply->deleteLater();
}
