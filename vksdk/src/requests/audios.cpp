#include "audios.h"

Audios::Audios(QObject *parent) : QObject(parent)
{}

Audios::~Audios()
{}

void Audios::setApi(ApiRequest *api) {
    _api = api;
}

void Audios::get(qint64 ownerId, int count) {
    QUrlQuery *query = new QUrlQuery();
    if (ownerId != 0) query->addQueryItem("owner_id", QString::number(ownerId));
    query->addQueryItem("count", QString::number(count));
    _api->makeApiGetRequest("audio.get", query, ApiRequest::AUDIO_GET);
}
