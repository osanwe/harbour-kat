#ifndef WALL_H
#define WALL_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QString>

#include "apirequest.h"
#include "objects/news.h"

class Wall : public QObject
{
    Q_OBJECT

public:
    explicit Wall(QObject *parent = 0);
    ~Wall();

    void setAccessToken(QString value);

    Q_INVOKABLE void getById(int ownerId, int id);

signals:
    void gotWallpost(News *news);

public slots:
    void gotResponse(QJsonValue value, ApiRequest::TaskType type);

private:
    QString _accessToken;
};

#endif // WALL_H
