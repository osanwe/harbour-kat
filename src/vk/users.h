#ifndef USERS_H
#define USERS_H

#include <QObject>
#include <QString>
#include <QUrlQuery>

#include "apirequest.h"

class Users : public QObject
{
    Q_OBJECT
public:
    explicit Users(QObject *parent = 0);
    ~Users();

    void setAccessToken(QString value);

    Q_INVOKABLE void get(int userId);

private:
    QString _accessToken;
};

#endif // USERS_H
