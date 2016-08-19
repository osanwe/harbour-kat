#ifndef NEWSFEED_H
#define NEWSFEED_H

#include <QList>

#include "apirequest.h"

class Newsfeed : public QObject
{
    Q_OBJECT

public:
    explicit Newsfeed(QObject *parent = 0);
    ~Newsfeed();

    void setApi(ApiRequest *api);

    Q_INVOKABLE void get(QString startFrom = "");

private:
    ApiRequest *_api;
};

#endif // NEWSFEED_H
