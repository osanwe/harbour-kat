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

    Q_INVOKABLE void get(qint64 ownerId = 0, int count = 6000);
    Q_INVOKABLE void search(QString query);

    void setApi(ApiRequest *api);

private:
    ApiRequest *_api;
};

#endif // AUDIOS_H
