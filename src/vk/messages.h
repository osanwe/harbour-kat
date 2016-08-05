#ifndef MESSAGES_H
#define MESSAGES_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QNetworkReply>
#include <QObject>
#include <QScopedPointer>
#include <QString>
#include <QVariant>

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

signals:
    void gotDialogs(QVariant dialogsModel);

public slots:
    void gotResponse(QJsonObject object);

private:
    QString _accessToken;
};

#endif // MESSAGES_H
