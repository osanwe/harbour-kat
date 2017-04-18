#ifndef STATS_H
#define STATS_H

#include "requestbase.h"

class Stats : public RequestBase
{
    Q_OBJECT
public:
    explicit Stats(QObject *parent = 0);

    Q_INVOKABLE void get(int id, const QString &from, const QString &to, bool isGroup = true);
    Q_INVOKABLE void trackVisitor();
};

#endif // STATS_H
