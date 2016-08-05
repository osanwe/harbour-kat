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
