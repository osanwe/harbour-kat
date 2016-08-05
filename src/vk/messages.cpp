#include "messages.h"

Messages::Messages(QObject *parent) : QObject(parent) {}

Messages::~Messages() {}

void Messages::setAccessToken(QString value) {
    _accessToken = value;
}

void Messages::getDialogs(int offset) {
    ApiRequest *request = new ApiRequest(this);
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("messages.getDialogs", new QUrlQuery(), ApiRequest::MESSAGES_GET_DIALOGS);
}

