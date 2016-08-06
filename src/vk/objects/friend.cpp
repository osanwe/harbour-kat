#include "friend.h"

Friend::Friend(QObject *parent) : QObject(parent)
{

}

Friend *Friend::fromJsonObject(QJsonObject object) {
    Friend *frnd = new Friend();
    frnd->setId(object.value("id").toInt());
    frnd->setFirstName(object.value("first_name").toString());
    frnd->setLastName(object.value("last_name").toString());
    if (object.contains("photo_50")) frnd->setPhoto50(object.value("photo_50").toString());
    if (object.contains("online")) frnd->setOnline(object.value("online").toInt() == 1);
    if (object.contains("status")) frnd->setStatus(object.value("status").toString());
    return frnd;
}

int Friend::id() const
{
    return _id;
}

void Friend::setId(int id)
{
    _id = id;
}

QString Friend::firstName() const
{
    return _firstName;
}

void Friend::setFirstName(const QString &firstName)
{
    _firstName = firstName;
}

QString Friend::lastName() const
{
    return _lastName;
}

void Friend::setLastName(const QString &lastName)
{
    _lastName = lastName;
}

QString Friend::photo50() const
{
    return _photo50;
}

void Friend::setPhoto50(const QString &photo50)
{
    _photo50 = photo50;
}

bool Friend::online() const
{
    return _online;
}

void Friend::setOnline(bool online)
{
    _online = online;
}

QString Friend::status() const
{
    return _status;
}

void Friend::setStatus(const QString &status)
{
    _status = status;
}

