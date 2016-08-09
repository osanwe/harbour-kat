#ifndef VIDEOS_H
#define VIDEOS_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QString>

#include "apirequest.h"
#include "objects/video.h"

class Videos : public QObject
{
    Q_OBJECT

public:
    explicit Videos(QObject *parent = 0);
    ~Videos();

    void setAccessToken(QString value);

    Q_INVOKABLE void get(int ownerId, int videoId);

signals:
    void gotVideo(Video* video);

public slots:
    void gotResponse(QJsonValue value, ApiRequest::TaskType type);

private:
    QString _accessToken;
};

#endif // VIDEOS_H
