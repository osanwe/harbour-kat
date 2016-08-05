#include "users.h"

Users::Users(QObject *parent) : QObject(parent)
{

}

Users::~Users()
{

}

void Users::setAccessToken(QString value) {
    _accessToken = value;
}

void Users::get(QStringList ids) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("user_ids", ids.join(","));
    query->addQueryItem("fields", "photo_50,online,status");
    ApiRequest *request = new ApiRequest();
    connect(request, SIGNAL(gotResponse(QJsonObject,ApiRequest::TaskType)),
            this, SLOT(gotResponse(QJsonObject,ApiRequest::TaskType)));
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("users.get", query, ApiRequest::USERS_GET);
}

void Users::gotResponse(QJsonValue object, ApiRequest::TaskType type) {
    switch (type) {
    case ApiRequest::USERS_GET:
        QJsonArray users = object.toArray();
        QList<QObject*> usersList;
        for (int index = 0; index < users.size(); ++index) {
            usersList.append(User::fromJsonObject(users.at(index).toObject()));
        }
        emit gotUsersList(usersList);
        break;
    }
}

