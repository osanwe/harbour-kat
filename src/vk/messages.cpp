#include "messages.h"

Messages::Messages(QObject *parent) : QObject(parent) {}

Messages::~Messages() {}

void Messages::setAccessTocken(QString value) {
    _accessToken = value;
}

void Messages::getLongPollServer() {
    QScopedPointer<ApiRequest> request(new ApiRequest(this));
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("messages.getLongPollServer", new QUrlQuery(), ApiRequest::MESSAGES_GET_LONG_POLL_SERVER);
}

void Messages::finished(QNetworkReply *reply, ApiRequest::TaskType type) {
    qDebug() << reply->readAll();
    switch (type) {
    case ApiRequest::MESSAGES_GET_LONG_POLL_SERVER:
        break;

    default:
        break;
    }

    reply->deleteLater();
}

