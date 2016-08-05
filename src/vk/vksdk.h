#ifndef VKSDK_H
#define VKSDK_H

#include <QObject>
#include <QString>

#include "longpoll.h"
#include "messages.h"

class VkSDK : public QObject
{
    Q_OBJECT

    Q_PROPERTY(LongPoll* longPoll READ longPoll CONSTANT)

public:
    explicit VkSDK(QObject *parent = 0);
    ~VkSDK();

    Q_INVOKABLE void setAccessTocken(QString value);

    LongPoll* longPoll() const;

private:
    QString _accessToken;

    LongPoll *_longPoll;
};

#endif // VKSDK_H
