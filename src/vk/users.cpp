#include "users.h"

Users::Users(QObject *parent) : QObject(parent)
{}

Users::~Users()
{}

void Users::setAccessToken(QString value) {
    _accessToken = value;
}

void Users::getSelfProfile() {
    getUserProfile(0);
}

void Users::getUserProfile(int id) {
    QUrlQuery *query = new QUrlQuery();
    if (id != 0) query->addQueryItem("user_ids", QString("%1").arg(id));
    query->addQueryItem("fields", "bdate,city,counters,online,photo_50,photo_200,photo_max_orig,relation,sex,status,verified");
    ApiRequest *request = new ApiRequest();
    connect(request, SIGNAL(gotResponse(QJsonValue,ApiRequest::TaskType)),
            this, SLOT(gotResponse(QJsonValue,ApiRequest::TaskType)));
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("users.get", query, ApiRequest::USERS_GET);
}

void Users::get(QStringList ids) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("user_ids", ids.join(","));
    query->addQueryItem("fields", "photo_50,online,status");
    ApiRequest *request = new ApiRequest();
    connect(request, SIGNAL(gotResponse(QJsonValue,ApiRequest::TaskType)),
            this, SLOT(gotResponse(QJsonValue,ApiRequest::TaskType)));
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("users.get", query, ApiRequest::USERS_GET_FRIENDS);
}

void Users::gotResponse(QJsonValue value, ApiRequest::TaskType type) {
    QJsonArray users;
    switch (type) {
    case ApiRequest::USERS_GET:
        users = value.toArray();
        if (users.size() == 1) emit gotUserProfile(User::fromJsonObject(users.at(0).toObject()));
        break;

    case ApiRequest::USERS_GET_FRIENDS:
        users = value.toArray();
        QList<QObject*> usersList;
        for (int index = 0; index < users.size(); ++index) {
            usersList.append(Friend::fromJsonObject(users.at(index).toObject()));
        }
        emit gotUsersList(usersList);
        break;
    }
}

