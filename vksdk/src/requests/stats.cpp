#include "stats.h"

Stats::Stats(QObject *parent) : RequestBase(parent)
{}

void Stats::get(int id, const QString &from, const QString &to, bool isGroup) {
    QUrlQuery query;
    query.addQueryItem(isGroup ? "group_id" : "app_id", QString::number(abs(id)));
    query.addQueryItem("date_from", from);
    query.addQueryItem("date_to", to);
    _api->makeApiGetRequest("stats.get", query, ApiRequest::STATS_GET);
}

void Stats::trackVisitor() {
    _api->makeApiGetRequest("stats.trackVisitor", QUrlQuery(), ApiRequest::STATS_TRACK_VISITOR);
}

