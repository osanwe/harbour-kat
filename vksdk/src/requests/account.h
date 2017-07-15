#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "requestbase.h"

class Account : public RequestBase
{
    Q_OBJECT
public:
    explicit Account(QObject *parent = 0);

    Q_INVOKABLE void setOnline();
    Q_INVOKABLE void banUser(int id);
    Q_INVOKABLE void unbanUser(int id);
};

#endif // ACCOUNT_H
