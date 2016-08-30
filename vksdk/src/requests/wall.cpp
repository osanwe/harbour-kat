#include "wall.h"

Wall::Wall(QObject *parent) : QObject(parent)
{}

Wall::~Wall()
{}

void Wall::setApi(ApiRequest *api) {
    _api = api;
}

void Wall::get(int ownerId, int offset) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("owner_id", QString::number(ownerId));
    query->addQueryItem("count", "20");
    query->addQueryItem("extended", "1");
    query->addQueryItem("fields", "photo_50");
    if (offset != 0) query->addQueryItem("offset", QString::number(offset));
    _api->makeApiGetRequest("wall.get", query, ApiRequest::WALL_GET);
}

void Wall::getById(int ownerId, int id) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("posts", QString("%1_%2").arg(ownerId).arg(id));
    _api->makeApiGetRequest("wall.getById", query, ApiRequest::WALL_GET_BY_ID);
}
