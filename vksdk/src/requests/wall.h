#ifndef WALL_H
#define WALL_H

#include <QObject>

#include "apirequest.h"

class Wall : public QObject
{
    Q_OBJECT

public:
    explicit Wall(QObject *parent = 0);
    ~Wall();

    void setApi(ApiRequest *api);

    Q_INVOKABLE void get(int ownerId, int offset = 0);
    Q_INVOKABLE void getById(int ownerId, int id);

private:
    ApiRequest *_api;
};

#endif // WALL_H
