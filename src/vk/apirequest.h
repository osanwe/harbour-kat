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

    enum TaskType {
        MESSAGES_GET_LONG_POLL_SERVER,
    };

    void makeApiGetRequest(QString method, QUrlQuery *query, TaskType type);
    void makePostRequest(QUrl url, QUrlQuery query, QByteArray body);

    void setAccessToken(QString token);

public slots:
    void finished(QNetworkReply *reply);

private:
    const QString API_URL = "https://api.vk.com/method/";
    const QString API_VERSION = "5.53";

    QString _accessToken;
    TaskType _currentTaskType;

    QNetworkAccessManager *_manager;
};

#endif // APIREQUEST_H
