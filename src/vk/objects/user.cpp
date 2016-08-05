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
    if (object.contains("bdate")) user->setBdate(object.value("bdate").toString());
    if (object.contains("city")) user->setCity(object.value("city").toObject().value("title").toString());
    if (object.contains("online")) user->setOnline(object.value("online").toBool());
    if (object.contains("photo_50")) user->setPhoto50(object.value("photo_50").toString());
    if (object.contains("photo_max_orig")) user->setPhotoMaxOrig(object.value("photo_max_orig").toString());
    if (object.contains("relation")) user->setRelation(object.value("relation").toInt());
    if (object.contains("sex")) user->setSex(object.value("sex").toInt());
    if (object.contains("status")) user->setStatus(object.value("status").toString());
    if (object.contains("verified")) user->setVerified(object.value("verified").toBool());
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

QString User::status() const
{
    return _status;
}

void User::setStatus(const QString &status)
{
    _status = status;
}

QString User::bdate() const
{
    return _bdate;
}

void User::setBdate(const QString &bdate)
{
    _bdate = bdate;
}

QString User::city() const
{
    return _city;
}

void User::setCity(const QString &city)
{
    _city = city;
}

bool User::online() const
{
    return _online;
}

void User::setOnline(bool online)
{
    _online = online;
}

QString User::photo50() const
{
    return _photo50;
}

void User::setPhoto50(const QString &photo50)
{
    _photo50 = photo50;
}

QString User::photoMaxOrig() const
{
    return _photoMaxOrig;
}

void User::setPhotoMaxOrig(const QString &photoMaxOrig)
{
    _photoMaxOrig = photoMaxOrig;
}

int User::relation() const
{
    return _relation;
}

void User::setRelation(int relation)
{
    _relation = relation;
}

int User::sex() const
{
    return _sex;
}

void User::setSex(int sex)
{
    _sex = sex;
}

bool User::verified() const
{
    return _verified;
}

void User::setVerified(bool verified)
{
    _verified = verified;
}

