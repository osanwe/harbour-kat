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

#include "user.h"

User::User(QObject *parent) : QObject(parent)
{}

User *User::fromJsonObject(QJsonObject object)
{
    qDebug() << object;
    User *user = new User();
    user->setId(object.value("id").toInt());
    user->setFirstName(object.value("first_name").toString());
    user->setLastName(object.value("last_name").toString());
    if (object.contains("bdate")) user->setBdate(object.value("bdate").toString());
    if (object.contains("city")) user->setCity(object.value("city").toObject().value("title").toString());
    if (object.contains("online")) user->setOnline(object.value("online").toInt());
    if (object.contains("photo_50")) user->setPhoto50(object.value("photo_50").toString());
    if (object.contains("photo_200")) user->setPhoto200(object.value("photo_200").toString());
    if (object.contains("photo_max_orig")) user->setPhotoMaxOrig(object.value("photo_max_orig").toString());
    if (object.contains("relation")) user->setRelation(object.value("relation").toInt());
    if (object.contains("sex")) user->setSex(object.value("sex").toInt());
    if (object.contains("status")) user->setStatus(object.value("status").toString());
    if (object.contains("verified")) user->setVerified(object.value("verified").toBool());
    if (object.contains("can_write_private_message")) user->setCanWritePrivateMessage(object.value("can_write_private_message").toInt() == 1);
    if (object.contains("relation_partner")) {
        QJsonObject partner = object.value("relation_partner").toObject();
        user->setRelationPartnerId(partner.value("id").toInt());
        user->setRelationPartnerName(partner.value("first_name").toString() + " " + partner.value("last_name").toString());
    }
    if (object.contains("counters")) {
        QJsonObject counters = object.value("counters").toObject();
        if (counters.contains("videos")) user->setVideosCounter(counters.value("videos").toInt());
        if (counters.contains("audios")) user->setAudiosCounter(counters.value("audios").toInt());
        if (counters.contains("photos")) user->setPhotosCounter(counters.value("photos").toInt());
        if (counters.contains("notes")) user->setNotesCounter(counters.value("notes").toInt());
        if (counters.contains("groups")) user->setGroupsCounter(counters.value("groups").toInt());
        if (counters.contains("pages")) user->setPagesCounter(counters.value("pages").toInt());
        if (counters.contains("friends")) user->setFriendsCounter(counters.value("friends").toInt());
        if (counters.contains("online_friends")) user->setOnlineFriendsCounter(counters.value("online_friends").toInt());
        if (counters.contains("mutual_friends")) user->setMutualFriendsCounter(counters.value("mutual_friends").toInt());
        if (counters.contains("followers")) user->setFollowersCounter(counters.value("followers").toInt());
    }
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

void User::setOnline(int online)
{
    _online = online == 1;
}

QString User::photo50() const
{
    return _photo50;
}

void User::setPhoto50(const QString &photo50)
{
    _photo50 = photo50;
}

QString User::photo200() const
{
    return _photo200;
}

void User::setPhoto200(const QString &photo200)
{
    _photo200 = photo200;
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

int User::videosCounter() const
{
    return _videosCounter;
}

void User::setVideosCounter(int videosCounter)
{
    _videosCounter = videosCounter;
}

int User::audiosCounter() const
{
    return _audiosCounter;
}

void User::setAudiosCounter(int audiosCounter)
{
    _audiosCounter = audiosCounter;
}

int User::photosCounter() const
{
    return _photosCounter;
}

void User::setPhotosCounter(int photosCounter)
{
    _photosCounter = photosCounter;
}

int User::notesCounter() const
{
    return _notesCounter;
}

void User::setNotesCounter(int notesCounter)
{
    _notesCounter = notesCounter;
}

int User::groupsCounter() const
{
    return _groupsCounter;
}

void User::setGroupsCounter(int groupsCounter)
{
    _groupsCounter = groupsCounter;
}

int User::pagesCounter() const
{
    return _pagesCounter;
}

void User::setPagesCounter(int pagesCounter)
{
    _pagesCounter = pagesCounter;
}

int User::friendsCounter() const
{
    return _friendsCounter;
}

void User::setFriendsCounter(int friendsCounter)
{
    _friendsCounter = friendsCounter;
}

int User::onlineFriendsCounter() const
{
    return _onlineFriendsCounter;
}

void User::setOnlineFriendsCounter(int onlineFriendsCounter)
{
    _onlineFriendsCounter = onlineFriendsCounter;
}

int User::mutualFriendsCounter() const
{
    return _mutualFriendsCounter;
}

void User::setMutualFriendsCounter(int mutualFriendsCounter)
{
    _mutualFriendsCounter = mutualFriendsCounter;
}

int User::followersCounter() const
{
    return _followersCounter;
}

void User::setFollowersCounter(int followersCounter)
{
    _followersCounter = followersCounter;
}

int User::relationPartnerId() const
{
    return _relationPartnerId;
}

void User::setRelationPartnerId(int relationPartnerId)
{
    _relationPartnerId = relationPartnerId;
}

QString User::relationPartnerName() const
{
    return _relationPartnerName;
}

void User::setRelationPartnerName(const QString &relationPartnerName)
{
    _relationPartnerName = relationPartnerName;
}

bool User::canWritePrivateMessage() const
{
    return _canWritePrivateMessage;
}

void User::setCanWritePrivateMessage(bool canWritePrivateMessage)
{
    _canWritePrivateMessage = canWritePrivateMessage;
}

