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
        QJsonArray _items = response.value("items").toArray();
        QJsonArray _profiles = response.value("profiles").toArray();
        QJsonArray _groups = response.value("groups").toArray();
        QString _nextFrom = response.value("next_from").toString();
        QList<News *> items;
        QList<User *> profiles;
        for (int index = 0; index < _items.size(); ++index) {
            items.append(News::fromJsonObject(_items.at(index).toObject()));
        }
        emit gotNewsfeed(items, profiles);
    }

    default:
        break;
    }
}

