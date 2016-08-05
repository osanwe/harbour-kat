#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QByteArray>
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

class ApiRequest : public QObject
{
    Q_OBJECT

public:
    explicit ApiRequest(QObject *parent = 0);
    ~ApiRequest();

    void makeGetRequest(QUrl url, QUrlQuery query);
    void makePostRequest(QUrl url, QUrlQuery query, QByteArray body);

public slots:
    void finished(QNetworkReply *reply);

private:
    QNetworkAccessManager *_manager;
};

#endif // APIREQUEST_H
