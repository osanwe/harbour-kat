#include "account.h"

Account::Account(QObject *parent) : QObject(parent)
{}

Account::~Account()
{}

void Account::setApi(ApiRequest *api) {
    _api = api;
}

void Account::setOnline() {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("voip", QString::number(0));
    _api->makeApiGetRequest("account.setOnline", query, ApiRequest::ACCOUNT_SET_ONLINE);
}
