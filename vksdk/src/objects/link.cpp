/*
  Copyright (C) 2016 Petr Vytovtov
  Contact: Petr Vytovtov <osanwe@protonmail.ch>
  All rights reserved.

  This file is part of Kat.

  Kat is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Kat is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Kat.  If not, see <http://www.gnu.org/licenses/>.
*/

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

