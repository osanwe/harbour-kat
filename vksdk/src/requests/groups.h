#ifndef GROUPS_H
#define GROUPS_H

#include <QObject>

#include "apirequest.h"

class Groups : public QObject
{
    Q_OBJECT

public:
    explicit Groups(QObject *parent = 0);
    ~Groups();

    void setApi(ApiRequest *api);

    Q_INVOKABLE void get(int userId = 0, int offset = 0);

private:
    ApiRequest *_api;
};

#endif // GROUPS_H
