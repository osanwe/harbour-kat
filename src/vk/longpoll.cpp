#include "longpoll.h"

LongPoll::LongPoll(QObject *parent) : QObject(parent) {
    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
}

LongPoll::~LongPoll() {
    delete _manager;
}

void LongPoll::setAccessToken(QString value) {
    _accessToken = value;
}

void LongPoll::getLongPollServer() {
    QUrl url("https://api.vk.com/method/messages.getLongPollServer");
    QUrlQuery query;
    query.addQueryItem("access_token", _accessToken);
    query.addQueryItem("v", "5.53");
    url.setQuery(query);
    _manager->get(QNetworkRequest(url));
}

void LongPoll::finished(QNetworkReply *reply) {
    QJsonDocument jDoc = QJsonDocument::fromJson(reply->readAll());
    if (_server.isNull() || _server.isEmpty()) {
        QJsonObject jObj = jDoc.object().value("response").toObject();
        _server = jObj.value("server").toString();
        _key = jObj.value("key").toString();
        _ts = jObj.value("ts").toInt();
        doLongPollRequest();
    } else {
        QJsonObject jObj = jDoc.object();
        if (jObj.contains("failed")) {
            if (jObj.value("failed").toInt() == 1) {
                _ts = jObj.value("ts").toInt();
                doLongPollRequest();
            } else {
                _server.clear();
                _key.clear();
                _ts = 0;
                getLongPollServer();
            }
        } else {
            _ts = jObj.value("ts").toInt();
//            qDebug() << jObj.value("updates").toArray();
            doLongPollRequest();
        }
    }
    reply->deleteLater();
}

void LongPoll::doLongPollRequest() {
    QUrl url("https://" + _server);
    QUrlQuery query;
    query.addQueryItem("act", "a_check");
    query.addQueryItem("key", _key);
    query.addQueryItem("ts", QString("%1").arg(_ts));
    query.addQueryItem("wait", "25");
    query.addQueryItem("mode", "10");
    url.setQuery(query);
    _manager->get(QNetworkRequest(url));
}

