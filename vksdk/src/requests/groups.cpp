#include "groups.h"

Groups::Groups(QObject *parent) : QObject(parent)
{}

Groups::~Groups()
{}

void Groups::setApi(ApiRequest *api) {
    _api = api;
}

void Groups::get(int userId, int offset) {
    QUrlQuery *query = new QUrlQuery();
    if (userId != 0) query->addQueryItem("user_id", QString::number(userId));
    if (offset != 0) query->addQueryItem("offset", QString::number(offset));
    query->addQueryItem("extended", "1");
    query->addQueryItem("fields", "status");
    _api->makeApiGetRequest("groups.get", query, ApiRequest::GROUPS_GET);
}

void Groups::getById(int groupId) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("group_id", QString::number(abs(groupId)));
    query->addQueryItem("fields", "description,members_count,counters,status");
    _api->makeApiGetRequest("groups.getById", query, ApiRequest::GROUPS_GET_BY_ID);
}

