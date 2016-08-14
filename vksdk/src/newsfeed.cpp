#include "newsfeed.h"

Newsfeed::Newsfeed(QObject *parent) : QObject(parent)
{}

Newsfeed::~Newsfeed()
{}

void Newsfeed::setAccessToken(QString value) {
    _accessToken = value;
}

void Newsfeed::get(QString startFrom) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("filters", "post");
    query->addQueryItem("return_banned", "0");
    query->addQueryItem("fields", "photo_50");
    if (!startFrom.isEmpty()) query->addQueryItem("start_from", startFrom);
    ApiRequest *request = new ApiRequest();
    connect(request, SIGNAL(gotResponse(QJsonValue,ApiRequest::TaskType)),
            this, SLOT(gotResponse(QJsonValue,ApiRequest::TaskType)));
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("newsfeed.get", query, ApiRequest::NEWSFEED_GET);
}

void Newsfeed::gotResponse(QJsonValue value, ApiRequest::TaskType type) {
    switch (type) {
    case ApiRequest::NEWSFEED_GET: {
        QJsonObject response = value.toObject();
        QJsonArray items = response.value("items").toArray();
        QJsonArray profiles = response.value("profiles").toArray();
        QJsonArray groups = response.value("groups").toArray();
        QString nextFrom = response.value("next_from").toString();
    }

    default:
        break;
    }
}

