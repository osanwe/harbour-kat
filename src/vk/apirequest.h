#ifndef APIREQUEST_H
#define APIREQUEST_H

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>

#include "objects/dialog.h"
#include "objects/message.h"

#include <QDebug>

class ApiRequest : public QObject
{
    Q_OBJECT

public:
    explicit ApiRequest(QObject *parent = 0);
    ~ApiRequest();

    enum TaskType {
        FRIENDS_GET,
        MESSAGES_GET_CHAT,
        MESSAGES_GET_DIALOGS,
        USERS_GET,
    };

    void makeApiGetRequest(QString method, QUrlQuery *query, TaskType type);
    void makePostRequest(QUrl url, QUrlQuery query, QByteArray body);

    void setAccessToken(QString token);

signals:
    void gotResponse(QJsonValue value, ApiRequest::TaskType type);

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
