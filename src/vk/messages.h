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

    void setAccessToken(QString value);

    Q_INVOKABLE void getDialogs(int offset = 0);

private:
    QString _accessToken;
};

#endif // MESSAGES_H
