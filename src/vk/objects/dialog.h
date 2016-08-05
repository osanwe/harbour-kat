#ifndef DIALOG_H
#define DIALOG_H

#include <QJsonObject>
#include <QObject>

#include "chat.h"
#include "message.h"
#include "user.h"

class Dialog : public QObject
{
    Q_OBJECT

public:
    explicit Dialog(QObject *parent = 0);

    static Dialog *fromJsonObject(QJsonObject object);

    bool unread() const;
    void setUnread(bool unread);

    bool isChat() const;
    void setIsChat(bool isChat);

    Message *lastMessage() const;
    void setLastMessage(Message *lastMessage);

    User *user() const;
    void setUser(User *user);

    Chat *chat() const;
    void setChat(Chat *chat);

private:
    bool _unread;
    bool _isChat;
    Message *_lastMessage;
    User *_user;
    Chat *_chat;
};

#endif // DIALOG_H
