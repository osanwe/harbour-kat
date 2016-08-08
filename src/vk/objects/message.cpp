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

#include "message.h"

Message::Message(QObject *parent) : QObject(parent)
{

}

Message *Message::fromJsonObject(QJsonObject object) {
    Message *message = new Message();
    message->setId(object.value("id").toInt());
    if (object.contains("user_id")) {
        message->setChat(false);
        message->setUserId(object.value("user_id").toInt());
    }
    if (object.contains("chat_id")) {
        message->setChat(true);
        message->setChatId(object.value("chat_id").toInt());
    }
    if (object.contains("from_id")) message->setFromId(object.value("from_id").toInt());
    if (object.contains("date")) message->setDate(object.value("date").toInt());
    if (object.contains("read_state")) message->setReadState(object.value("read_state").toInt() == 1);
    if (object.contains("out")) message->setOut(object.value("out").toInt() == 1);
    if (object.contains("body")) message->setBody(object.value("body").toString());
    if (object.contains("geo")) {
        QJsonObject geo = object.value("geo").toObject();
        QStringList coords = geo.value("coordinates").toString().split(" ");
        message->setGeoMap(coords.at(0).toDouble(), coords.at(1).toDouble());
        message->setGeoTile(coords.at(0).toDouble(), coords.at(1).toDouble());
    }
    // TODO: Attachments
    if (object.contains("fwd_messages")) {
        QJsonArray fwds = object.value("fwd_messages").toArray();
        for (int index = 0; index < fwds.size(); ++index) {
            QJsonObject fwd = fwds.at(index).toObject();
            message->addFwdMessages(Message::fromJsonObject(fwd));
        }
    }
    return message;
}

int Message::id() const
{
    return _id;
}

void Message::setId(int id)
{
    _id = id;
}

int Message::userId() const
{
    return _userId;
}

void Message::setUserId(int userId)
{
    _userId = userId;
}

int Message::chatId() const
{
    return _chatId;
}

void Message::setChatId(int chatId)
{
    _chatId = chatId;
}

int Message::fromId() const
{
    return _fromId;
}

void Message::setFromId(int fromId)
{
    _fromId = fromId;
}

int Message::date() const
{
    return _date;
}

void Message::setDate(int date)
{
    _date = date;
}

bool Message::readState() const
{
    return _readState;
}

void Message::setReadState(bool readState)
{
    _readState = readState;
}

bool Message::out() const
{
    return _out;
}

void Message::setOut(bool out)
{
    _out = out;
}

QString Message::body() const
{
    return _body;
}

void Message::setBody(const QString &body)
{
    _body = body;
}

QVariant Message::fwdMessages() const
{
    return QVariant::fromValue(_fwdMessages);
}

QList<QObject *> Message::fwdMessagesList() const {
    return _fwdMessages;
}

void Message::addFwdMessages(Message *message)
{
    _fwdMessages.append(message);
}

QString Message::geoTile() const
{
    return _geoTile;
}

void Message::setGeoTile(double lat, double lon)
{
    _geoTile = QString("http://www.mapquestapi.com/staticmap/v4/getmap?key=AfRC0WKf0YDWjtNKyWuB3LCpdHUQeME6&size=400,200&zoom=18&center=%1,%2").arg(lat).arg(lon);
}

QString Message::geoMap() const
{
    return _geoMap;
}

void Message::setGeoMap(double lat, double lon)
{
    _geoMap = QString("http://www.openstreetmap.org/?mlat=%1&mlon=%2&zoom=19").arg(lat).arg(lon);
}

bool Message::chat() const
{
    return _chat;
}

void Message::setChat(bool chat)
{
    _chat = chat;
}

