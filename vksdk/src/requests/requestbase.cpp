#include "requestbase.h"

RequestBase::RequestBase(QObject *parent) :
    QObject(parent),
    _api(nullptr)
{
}

void RequestBase::setApi(ApiRequest *api)
{
    _api = api;
}
