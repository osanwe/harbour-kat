#ifndef STATS_H
#define STATS_H

#include <QObject>

#include "apirequest.h"

class Stats : public QObject
{
    Q_OBJECT

public:
    explicit Stats(QObject *parent = 0);
    ~Stats();

    void setApi(ApiRequest *api);

    Q_INVOKABLE void get(int id, QString from, QString to, bool isGroup = true);
    Q_INVOKABLE void trackVisitor();

private:
    ApiRequest *_api;
};

#endif // STATS_H
