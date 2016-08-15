#include "group.h"

Group::Group(QObject *parent) : QObject(parent)
{}

Group *Group::fromJsonObject(QJsonObject object)
{
    Group *group = new Group();
    if (object.contains("id")) group->setId(object.value("id").toInt());
    if (object.contains("name")) group->setName(object.value("name").toString());
    if (object.contains("photo_50")) group->setPhoto50(object.value("photo_50").toString());
    if (object.contains("photo_100")) group->setPhoto100(object.value("photo_100").toString());
    if (object.contains("photo_200")) group->setPhoto200(object.value("photo_200").toString());
    return group;
}

int Group::id() const
{
    return _id;
}

void Group::setId(int id)
{
    _id = -id;
}

QString Group::name() const
{
    return _name;
}

void Group::setName(const QString &name)
{
    _name = name;
}

QString Group::photo50() const
{
    return _photo50;
}

void Group::setPhoto50(const QString &photo50)
{
    _photo50 = photo50;
}

QString Group::photo100() const
{
    return _photo100;
}

void Group::setPhoto100(const QString &photo100)
{
    _photo100 = photo100;
}

QString Group::photo200() const
{
    return _photo200;
}

void Group::setPhoto200(const QString &photo200)
{
    _photo200 = photo200;
}

