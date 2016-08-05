#include "dialog.h"

Dialog::Dialog(QObject *parent) : QObject(parent)
{}

Dialog *Dialog::fromJsonObject(QJsonObject object) {
    Dialog *dialog = new Dialog();
    dialog->setUnread(object.contains("unread"));
    dialog->setLastMessage(object.value("message").toObject());
    return dialog;
}

bool Dialog::unread() const
{
    return _unread;
}

void Dialog::setUnread(bool unread)
{
    _unread = unread;
}

Message *Dialog::lastMessage() const
{
    return _lastMessage;
}

void Dialog::setLastMessage(Message *lastMessage)
{
    _lastMessage = lastMessage;
}

