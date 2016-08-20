#ifndef VIDEOS_H
#define VIDEOS_H

//#include <QJsonArray>
//#include <QJsonObject>
//#include <QJsonValue>
#include <QObject>
//#include <QString>

#include "apirequest.h"
//#include "objects/video.h"

class Videos : public QObject
{
    Q_OBJECT

public:
    explicit Videos(QObject *parent = 0);
    ~Videos();

    Q_INVOKABLE void get(int ownerId, int videoId);

    void setApi(ApiRequest *api);

private:
    ApiRequest *_api;
};

#endif // VIDEOS_H
