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
    Q_PROPERTY(Messages* messages READ messages CONSTANT)

public:
    explicit VkSDK(QObject *parent = 0);
    ~VkSDK();

    Q_INVOKABLE void setAccessTocken(QString value);

    LongPoll* longPoll() const;
    Messages* messages() const;

private:
    QString _accessToken;

    LongPoll *_longPoll;
    Messages *_messages;
};

#endif // VKSDK_H
