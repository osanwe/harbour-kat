#ifndef DIALOG_H
#define DIALOG_H

#include <QJsonObject>
#include <QObject>

#include "message.h"

class Dialog : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool unread READ unread CONSTANT)
    Q_PROPERTY(Message* lastMessage READ lastMessage CONSTANT)

public:
    explicit Dialog(QObject *parent = 0);

    static Dialog *fromJsonObject(QJsonObject object);

    bool unread() const;
    void setUnread(bool unread);

    Message *lastMessage() const;
    void setLastMessage(Message *lastMessage);

private:
    bool _unread;
    Message *_lastMessage;
};

#endif // DIALOG_H
