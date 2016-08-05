#ifndef MESSAGES_H
#define MESSAGES_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QObject>
#include <QScopedPointer>
#include <QString>

#include "apirequest.h"

#include <QDebug>

class Messages : public QObject
{
    Q_OBJECT

public:
    explicit Messages(QObject *parent = 0);
    ~Messages();

    void setAccessTocken(QString value);

    Q_INVOKABLE void getLongPollServer();

public slots:
    void finished(QNetworkReply *reply, ApiRequest::TaskType type);

private:
    QString _accessToken;
};

#endif // MESSAGES_H
