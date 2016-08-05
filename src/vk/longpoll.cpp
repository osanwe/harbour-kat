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
            parseLongPollUpdates(jObj.value("updates").toArray());
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

void LongPoll::parseLongPollUpdates(QJsonArray updates) {
    for (int index = 0; index < updates.size(); ++index) {
        QJsonArray update = updates.at(index).toArray();
        switch (update.at(0).toInt()) {
        case 4:
            qDebug() << "--------------";
            qDebug() << "The message was sent";
            qDebug() << "\tflags:" << update.at(1).toInt();
            qDebug() << "\tfrom:" << update.at(2).toInt();
            qDebug() << "\ttimestamp:" << update.at(3).toInt();
            qDebug() << "\tsubject" << update.at(4).toString();
            qDebug() << "\ttext:" << update.at(5).toString();
            qDebug() << "\tin" << update.at(6).toArray();
            qDebug() << "--------------";
            break;

        case 6:
        case 7:
            qDebug() << "--------------";
            qDebug() << "Messages were readed";
            qDebug() << "\tfrom" + update.at(1).toInt() << "to" << update.at(2).toInt();
            qDebug() << "--------------";
            break;

        case 8:
            qDebug() << "--------------";
            qDebug() << "User" << update.at(1).toInt() << "is online";
            qDebug() << "--------------";
            break;

        case 9:
            qDebug() << "--------------";
            qDebug() << "User" << update.at(1).toInt() << "is offline";
            qDebug() << "--------------";
            break;

        case 61:
            qDebug() << "--------------";
            qDebug() << "User" << update.at(1).toInt() << "typing...";
            qDebug() << "--------------";
            break;

        case 62:
            qDebug() << "--------------";
            qDebug() << "User" << update.at(1).toInt() << "typing...";
            qDebug() << "\tin" << update.at(2).toInt();
            qDebug() << "--------------";
            break;

        case 80:
            qDebug() << "--------------";
            qDebug() << "Unread dialogs:" << update.at(1).toInt();
            qDebug() << "--------------";
            break;

        default:
            break;
        }
    }
}

