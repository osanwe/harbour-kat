#include "likes.h"

Likes::Likes(QObject *parent) : QObject(parent)
{}

Likes::~Likes()
{}

void Likes::setApi(ApiRequest *api) {
    _api = api;
}

void Likes::addPost(int ownerId, int itemId) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("type", "post");
    query->addQueryItem("owner_id", QString("%1").arg(ownerId));
    query->addQueryItem("item_id", QString("%1").arg(itemId));
    _api->makeApiGetRequest("likes.add", query, ApiRequest::LIKES_ADD);
}

//void Likes::gotResponse(QJsonValue value, ApiRequest::TaskType type) {
//    switch (type) {
//    case ApiRequest::LIKES_ADD:
//        emit addedLike(value.toObject().value("likes").toInt());
//        break;

//    default:
//        break;
//    }
//}

