#ifndef NEWSFEED_H
#define NEWSFEED_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QString>
#include <QUrlQuery>

#include "apirequest.h"

#include <QDebug>

class Newsfeed : public QObject
{
    Q_OBJECT

public:
    explicit Newsfeed(QObject *parent = 0);
    ~Newsfeed();

    void setAccessToken(QString value);

    Q_INVOKABLE void get(QString startFrom = "");

signals:
    void gotNewsfeed(QList<QObject *> newsfeedList);

public slots:
    void gotResponse(QJsonValue value, ApiRequest::TaskType type);

private:
    QString _accessToken;
};

#endif // NEWSFEED_H
