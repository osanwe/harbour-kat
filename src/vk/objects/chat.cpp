#include "chat.h"

Chat::Chat(QObject *parent) : QObject(parent)
{

}

const Chat *Chat::fromJsonObject(QJsonObject object)
{
    Chat *chat = new Chat();
    chat->setId(object.value("id").toInt());
    chat->setTitle(object.value("title").toString());
    if (object.contains("photo_50")) chat->setPhoto(object.value("photo_50").toString());
    chat->setUsers(object.value("users").toArray().toVariantList());
    return chat;
}

int Chat::id() const
{
    return _id;
}

void Chat::setId(int id)
{
    _id = id;
}

QString Chat::title() const
{
    return _title;
}

void Chat::setTitle(const QString &title)
{
    _title = title;
}

QString Chat::photo() const
{
    return _photo;
}

void Chat::setPhoto(const QString &photo)
{
    _photo = photo;
}

QVariantList Chat::users() const
{
    return _users;
}

void Chat::setUsers(const QVariantList &users)
{
    _users = users;
}

