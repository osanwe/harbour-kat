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
    Q_INVOKABLE void banUser(int id);
    Q_INVOKABLE void unbanUser(int id);

private:
    ApiRequest *_api;
};

#endif // ACCOUNT_H
