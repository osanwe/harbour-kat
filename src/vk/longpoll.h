#ifndef LONGPOLL_H
#define LONGPOLL_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QUrlQuery>

#include <QDebug>

class LongPoll : public QObject
{
    Q_OBJECT

public:
    explicit LongPoll(QObject *parent = 0);
    ~LongPoll();

    void setAccessToken(QString value);

    Q_INVOKABLE void getLongPollServer();

signals:
    void unreadDialogsCounterUpdated(int value);

public slots:
    void finished(QNetworkReply *reply);

private:
    QString _accessToken;
    QString _server;
    QString _key;
    int _ts;

    QNetworkAccessManager *_manager;

    void doLongPollRequest();
    void parseLongPollUpdates(QJsonArray updates);
};

#endif // LONGPOLL_H
