#ifndef AUDIOS_H
#define AUDIOS_H

#include <QObject>

#include "apirequest.h"

class Audios : public QObject
{
    Q_OBJECT

public:
    explicit Audios(QObject *parent = 0);
    ~Audios();

    void setApi(ApiRequest *api);

    Q_INVOKABLE void add(qint64 ownerId, qint64 audioId);
    Q_INVOKABLE void get(qint64 ownerId = 0, int count = 6000);
    Q_INVOKABLE void search(QString query);

private:
    ApiRequest *_api;
};

#endif // AUDIOS_H
