#include "authorization.h"

Authorization::Authorization(QObject *parent) : QObject(parent)
{}

Authorization::~Authorization()
{}

QString Authorization::buildAuthUrl() {
    QUrl url("https://oauth.vk.com/authorize");
    QUrlQuery query;
    query.addQueryItem("client_id", "4803503");
    query.addQueryItem("redirect_uri", "https://oauth.vk.com/blank.html");
    query.addQueryItem("display", "mobile");
    query.addQueryItem("scope", "friends,photos,audio,video,docs,notes,pages,status,wall,groups,messages,notifications,offline");
    query.addQueryItem("response_type", "token");
    query.addQueryItem("v", "5.53");
    url.setQuery(query);
    return url.toString();
}

void Authorization::tryToGetAccessToken(QString url) {
    QUrlQuery query(QUrl(url).fragment());
    if (query.hasQueryItem("access_token")) {
        emit authorized(query.queryItemValue("access_token"), query.queryItemValue("user_id"));
    } else if (query.hasQueryItem("error")) {
        emit error(query.queryItemValue("error"), query.queryItemValue("error_description"));
    }
}
