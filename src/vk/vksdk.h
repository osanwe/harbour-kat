#ifndef VKSDK_H
#define VKSDK_H

#include <QObject>
#include <QString>

#include "apirequest.h"

class VkSDK : public QObject
{
    Q_OBJECT

public:
    explicit VkSDK(QObject *parent = 0);
    ~VkSDK();

    Q_INVOKABLE void setAccessTocken(QString value);

private:
    QString _accessToken;
    ApiRequest *_request;
};

#endif // VKSDK_H
