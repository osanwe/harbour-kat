#ifndef USERS_H
#define USERS_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QString>
#include <QUrlQuery>

#include "apirequest.h"
#include "objects/user.h"

#include <QDebug>

class Users : public QObject
{
    Q_OBJECT
public:
    explicit Users(QObject *parent = 0);
    ~Users();

    void setAccessToken(QString value);

    Q_INVOKABLE void get(int userId);

signals:
    void gotUsersList(QList<QObject*> usersList);

public slots:
    void gotResponse(QJsonValue object, ApiRequest::TaskType type);

private:
    QString _accessToken;
};

#endif // USERS_H
