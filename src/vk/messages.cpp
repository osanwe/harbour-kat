#include "messages.h"

Messages::Messages(QObject *parent) : QObject(parent) {}

Messages::~Messages() {}

void Messages::setAccessToken(QString value) {
    _accessToken = value;
}

void Messages::getDialogs(int offset) {
    ApiRequest *request = new ApiRequest(this);
    connect(request, SIGNAL(gotDialogs(QJsonObject)), this, SLOT(gotResponse(QJsonObject)));
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("messages.getDialogs", new QUrlQuery(), ApiRequest::MESSAGES_GET_DIALOGS);
}

void Messages::gotResponse(QJsonObject object) {
    QJsonArray dialogs = object.value("items").toArray();
    QList<QObject*> dialogsList;
    for (int index = 0; index < dialogs.size(); ++index) {
        dialogsList.append(Dialog::fromJsonObject(dialogs.at(index).toObject()));
    }
    emit gotDialogs(QVariant::fromValue(dialogsList));
}

