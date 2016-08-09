#include "videos.h"

Videos::Videos(QObject *parent) : QObject(parent)
{}

Videos::~Videos()
{}

void Videos::setAccessToken(QString value) {
    _accessToken = value;
}

void Videos::get(int ownerId, int videoId) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("owner_id", QString("%1").arg(ownerId));
    query->addQueryItem("videos", QString("%1_%2").arg(ownerId).arg(videoId));
    ApiRequest *request = new ApiRequest();
    connect(request, SIGNAL(gotResponse(QJsonValue,ApiRequest::TaskType)),
            this, SLOT(gotResponse(QJsonValue,ApiRequest::TaskType)));
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("video.get", query, ApiRequest::VIDEO_GET);
}

void Videos::gotResponse(QJsonValue value, ApiRequest::TaskType type)
{
    switch (type) {
    case ApiRequest::VIDEO_GET: {
        QJsonArray items = value.toObject().value("items").toArray();
        emit gotVideo(Video::fromJsonObject(items.at(0).toObject()));
        break;
    }

    default:
        break;
    }
}

