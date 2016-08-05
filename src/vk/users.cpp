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
    query->addQueryItem("fields", "bdate,city,online,photo_50,photo_max_orig,relation,sex,status,verified");
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
    connect(request, SIGNAL(gotResponse(QJsonObject,ApiRequest::TaskType)),
            this, SLOT(gotResponse(QJsonObject,ApiRequest::TaskType)));
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("users.get", query, ApiRequest::USERS_GET);
}

void Users::gotResponse(QJsonValue value, ApiRequest::TaskType type) {
    switch (type) {
    case ApiRequest::USERS_GET:
        QJsonArray users = value.toArray();
        if (users.size() == 1) emit gotUserProfile(User::fromJsonObject(users.at(0).toObject()));
//        QJsonArray users = object.toArray();
//        QList<QObject*> usersList;
//        for (int index = 0; index < users.size(); ++index) {
//            usersList.append(User::fromJsonObject(users.at(index).toObject()));
//        }
//        emit gotUsersList(usersList);
        break;
    }
}

