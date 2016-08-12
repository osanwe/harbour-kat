#include "wall.h"

Wall::Wall(QObject *parent) : QObject(parent)
{}

Wall::~Wall()
{}

void Wall::setAccessToken(QString value) {
    _accessToken = value;
}

void Wall::getById(int ownerId, int id) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("posts", QString("%1_%2").arg(ownerId).arg(id));
    ApiRequest *request = new ApiRequest();
    connect(request, SIGNAL(gotResponse(QJsonValue,ApiRequest::TaskType)),
            this, SLOT(gotResponse(QJsonValue,ApiRequest::TaskType)));
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("wall.getById", query, ApiRequest::WALL_GET_BY_ID);
}

void Wall::gotResponse(QJsonValue value, ApiRequest::TaskType type)
{
    switch (type) {
    case ApiRequest::WALL_GET_BY_ID: {
        QJsonArray items = value.toObject().value("items").toArray();
        emit gotWallpost(News::fromJsonObject(items.at(0).toObject()));
        break;
    }

    default:
        break;
    }
}

