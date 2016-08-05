#include "users.h"

Users::Users(QObject *parent) : QObject(parent)
{

}

void Users::setAccessToken(QString value) {
    _accessToken = value;
}

void Users::get(int userId) {
    QUrlQuery *query = new QUrlQuery();
    query.addQueryItem("user_ids", QString("%1").arg(userId));
    query.addQueryItem("fields", "photo_50");
    ApiRequest *request = new ApiRequest();
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("users.get", query, ApiRequest::USERS_GET);
}

