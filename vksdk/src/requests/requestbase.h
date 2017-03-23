#ifndef REQUESTBASE_H
#define REQUESTBASE_H

#include "apirequest.h"
class RequestBase : public QObject
{
public:
    RequestBase(QObject *parent = nullptr);
    void setApi(ApiRequest *api);

protected:
    ApiRequest *_api;
};

#endif // REQUESTBASE
