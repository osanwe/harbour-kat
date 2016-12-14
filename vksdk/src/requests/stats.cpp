#include "stats.h"

Stats::Stats(QObject *parent) : QObject(parent)
{}

Stats::~Stats()
{}

void Stats::setApi(ApiRequest *api) {
    _api = api;
}

void Stats::trackVisitor() {
    _api->makeApiGetRequest("stats.trackVisitor", new QUrlQuery(), ApiRequest::STATS_TRACK_VISITOR);
}

