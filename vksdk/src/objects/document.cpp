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

#include "document.h"

Document::Document(QObject *parent) : QObject(parent)
{

}

Document *Document::fromJsonObject(QJsonObject object)
{
    Document *document = new Document();
    if (object.contains("id")) document->setId(object.value("id").toInt());
    if (object.contains("owner_id")) document->setOwnerId(object.value("owner_id").toInt());
    if (object.contains("size")) document->setSize(object.value("size").toInt());
    if (object.contains("title")) document->setTitle(object.value("title").toString());
    if (object.contains("url")) document->setUrl(object.value("url").toString());
    // TODO: getting preview
    if (object.contains("photo_100")) document->setPhoto100(object.value("photo_100").toString());
    if (object.contains("photo_130")) document->setPhoto130(object.value("photo_130").toString());
    return document;
}

int Document::id() const
{
    return _id;
}

void Document::setId(int id)
{
    _id = id;
}

int Document::ownerId() const
{
    return _ownerId;
}

void Document::setOwnerId(int ownerId)
{
    _ownerId = ownerId;
}

int Document::size() const
{
    return _size;
}

void Document::setSize(int size)
{
    _size = size;
}

QString Document::title() const
{
    return _title;
}

void Document::setTitle(const QString &title)
{
    _title = title;
}

QString Document::url() const
{
    return _url;
}

void Document::setUrl(const QString &url)
{
    _url = url;
}

bool Document::hasPhoto() const
{
    return !_photo130.isEmpty() || !_photo100.isEmpty();
}

QString Document::photo() const
{
    if (!_photo130.isEmpty()) return _photo130;
    return _photo100;
}

void Document::setPhoto100(const QString &photo100)
{
    _photo100 = photo100;
}

void Document::setPhoto130(const QString &photo130)
{
    _photo130 = photo130;
}

