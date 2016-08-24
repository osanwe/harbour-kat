#include "link.h"

Link::Link(QObject *parent) : QObject(parent)
{}

Link *Link::fromJsonObject(QJsonObject object) {
    Link *link = new Link();
    if (object.contains("url")) link->setUrl(object.value("url").toString());
    if (object.contains("title")) link->setTitle(object.value("title").toString());
    return link;
}

QString Link::url() const
{
    return _url;
}

void Link::setUrl(const QString &url)
{
    _url = url;
}

QString Link::title() const
{
    return _title;
}

void Link::setTitle(const QString &title)
{
    _title = title;
}

