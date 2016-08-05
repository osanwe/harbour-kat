#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}

User *User::fromJsonObject(QJsonObject object)
{
    User *user = new User();
    user->setId(object.value("id").toInt());
    user->setFirstName(object.value("first_name").toString());
    user->setLastName(object.value("last_name").toString());
    user->setPhoto(object.value("photo_50").toString());
    user->setStatus(object.value("status").toString());
    user->setIsOnline(object.value("online").toBool());
    return user;
}

int User::id() const
{
    return _id;
}

void User::setId(int id)
{
    _id = id;
}

QString User::firstName() const
{
    return _firstName;
}

void User::setFirstName(const QString &firstName)
{
    _firstName = firstName;
}

QString User::lastName() const
{
    return _lastName;
}

void User::setLastName(const QString &lastName)
{
    _lastName = lastName;
}

QString User::photo() const
{
    return _photo;
}

void User::setPhoto(const QString &photo)
{
    _photo = photo;
}

QString User::status() const
{
    return _status;
}

void User::setStatus(const QString &status)
{
    _status = status;
}

bool User::isOnline() const
{
    return _isOnline;
}

void User::setIsOnline(bool isOnline)
{
    _isOnline = isOnline;
}

