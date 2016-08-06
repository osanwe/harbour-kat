#ifndef FRIENDS_H
#define FRIENDS_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QList>
#include <QObject>
#include <QString>
#include <QVariantList>
#include <QUrlQuery>

#include "apirequest.h"
#include "objects/friend.h"

#include <QDebug>

class Friends : public QObject
{
    Q_OBJECT

public:
    explicit Friends(QObject *parent = 0);
    ~Friends();

    void setAccessToken(QString value);

    Q_INVOKABLE void get(int userId);
    Q_INVOKABLE void getOnline(int userId);
    Q_INVOKABLE void getMutual(int userId);

signals:
    void gotFriendsList(QList<QObject*> friendsList);
    void gotMutualFriendsIds(QVariantList ids);

public slots:
    void gotResponse(QJsonValue value, ApiRequest::TaskType type);

private:
    QString _accessToken;
};

#endif // FRIENDS_H
