#ifndef LIKES_H
#define LIKES_H

#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QString>
#include <QUrlQuery>

#include "apirequest.h"

class Likes : public QObject
{
    Q_OBJECT
public:
    explicit Likes(QObject *parent = 0);
    ~Likes();

    void setAccessToken(QString value);

    Q_INVOKABLE void addPost(int ownerId, int itemId);

signals:
    void addedLike(int likesCount);

public slots:
    void gotResponse(QJsonValue value, ApiRequest::TaskType type);

private:
    QString _accessToken;
};

#endif // LIKES_H
