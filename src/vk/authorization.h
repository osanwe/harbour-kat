#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QUrlQuery>

#include <QDebug>

class Authorization : public QObject
{
    Q_OBJECT

public:
    explicit Authorization(QObject *parent = 0);
    ~Authorization();

    Q_INVOKABLE QString buildAuthUrl();
    Q_INVOKABLE void tryToGetAccessToken(QString url);

signals:
    void authorized(QString accessToken, QString userId);
    void error(QString errorCode, QString errorMessage);
};

#endif // AUTHORIZATION_H
