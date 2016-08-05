#ifndef MESSAGES_H
#define MESSAGES_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include <QNetworkReply>
#include <QObject>
#include <QScopedPointer>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "apirequest.h"
#include "objects/chat.h"

#include <QDebug>

class Messages : public QObject
{
    Q_OBJECT

public:
    explicit Messages(QObject *parent = 0);
    ~Messages();

    void setAccessToken(QString value);

    Q_INVOKABLE void getChat(QStringList ids);
    Q_INVOKABLE void getDialogs(int offset = 0);

signals:
    void gotChatsList(QList<QObject*> chatsList);
    void gotDialogsList(QList<QObject*> dialogsList);

public slots:
    void gotResponse(QJsonValue value, ApiRequest::TaskType type);

private:
    QString _accessToken;
};

#endif // MESSAGES_H
