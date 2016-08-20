#ifndef LIKES_H
#define LIKES_H

//#include <QJsonObject>
//#include <QJsonValue>
#include <QObject>
//#include <QString>
//#include <QUrlQuery>

#include "apirequest.h"

class Likes : public QObject
{
    Q_OBJECT
public:
    explicit Likes(QObject *parent = 0);
    ~Likes();

    Q_INVOKABLE void addPost(int ownerId, int itemId);

    void setApi(ApiRequest *api);

private:
    ApiRequest *_api;
};

#endif // LIKES_H
