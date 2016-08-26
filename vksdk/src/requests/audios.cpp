#include "audios.h"

Audios::Audios(QObject *parent) : QObject(parent)
{}

Audios::~Audios()
{}

void Audios::setApi(ApiRequest *api) {
    _api = api;
}

void Audios::add(qint64 ownerId, qint64 audioId) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("owner_id", QString::number(ownerId));
    query->addQueryItem("audio_id", QString::number(audioId));
    _api->makeApiGetRequest("audio.add", query, ApiRequest::AUDIO_ADD);
}

void Audios::get(qint64 ownerId, int count) {
    QUrlQuery *query = new QUrlQuery();
    if (ownerId != 0) query->addQueryItem("owner_id", QString::number(ownerId));
    query->addQueryItem("count", QString::number(count));
    _api->makeApiGetRequest("audio.get", query, ApiRequest::AUDIO_GET);
}

void Audios::search(QString _query) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("q", _query);
    query->addQueryItem("auto_complete", "1");
    query->addQueryItem("lyrics", "0");
    query->addQueryItem("performer_only", "0");
    query->addQueryItem("sort", "2");
    query->addQueryItem("count", "300");
    _api->makeApiGetRequest("audio.search", query, ApiRequest::AUDIO_SEARCH);
}
