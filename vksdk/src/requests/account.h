#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>

#include "apirequest.h"

class Account : public QObject
{
    Q_OBJECT

public:
    explicit Account(QObject *parent = 0);
    ~Account();

    void setApi(ApiRequest *api);

    Q_INVOKABLE void setOnline();

private:
    ApiRequest *_api;
};

#endif // ACCOUNT_H
