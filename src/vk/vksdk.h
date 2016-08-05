#ifndef VKSDK_H
#define VKSDK_H

#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>

#include "longpoll.h"
#include "messages.h"
#include "users.h"
#include "objects/chat.h"
#include "objects/dialog.h"
#include "objects/user.h"

class VkSDK : public QObject
{
    Q_OBJECT

    Q_PROPERTY(LongPoll* longPoll READ longPoll CONSTANT)
    Q_PROPERTY(Messages* messages READ messages CONSTANT)
    Q_PROPERTY(Users* users READ users CONSTANT)

public:
    explicit VkSDK(QObject *parent = 0);
    ~VkSDK();

    Q_INVOKABLE void setAccessTocken(QString value);

    LongPoll* longPoll() const;
    Messages* messages() const;
    Users* users() const;

public slots:
    void gotChatsList(QList<QObject*> chatsList);
    void gotDialogList(QList<QObject*> dialogsList);
    void gotUsersList(QList<QObject*> usersList);

private:
    QString _accessToken;

    LongPoll *_longPoll;
    Messages *_messages;
    Users *_users;

    QStringList _usersIds;
    QStringList _chatsIds;
    QList<QObject*> _dialogs;
};

#endif // VKSDK_H
