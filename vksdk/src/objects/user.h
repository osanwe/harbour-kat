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

#ifndef USER_H
#define USER_H

#include <QJsonObject>
#include <QObject>
#include <QString>

#include <QDebug>

class User : public QObject
{
    Q_OBJECT

    // System
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QString deactivated READ deactivated CONSTANT)
    Q_PROPERTY(bool blacklisted READ blacklisted CONSTANT)
    Q_PROPERTY(bool blacklistedByMe READ blacklistedByMe CONSTANT)
    Q_PROPERTY(bool canPost READ canPost CONSTANT)
    Q_PROPERTY(bool canSeeAllPosts READ canSeeAllPosts CONSTANT)
    Q_PROPERTY(bool canSeeAudio READ canSeeAudio CONSTANT)
    Q_PROPERTY(bool canSendFriendRequest READ canSendFriendRequest CONSTANT)
    Q_PROPERTY(bool canWritePrivateMessage READ canWritePrivateMessage CONSTANT)
    Q_PROPERTY(QString domain READ domain CONSTANT)
//    Q_PROPERTY(T<?> exports READ exports CONSTANT)
    Q_PROPERTY(int friendStatus READ friendStatus CONSTANT)
    Q_PROPERTY(bool isFavorite READ isFavorite CONSTANT)
    Q_PROPERTY(bool isHiddenFromFeed READ isHiddenFromFeed CONSTANT)
    Q_PROPERTY(QString photoMaxOrig READ photoMaxOrig CONSTANT)
    Q_PROPERTY(bool verified READ getVerified CONSTANT)

//    Q_PROPERTY(QString firstName READ firstName CONSTANT)
//    Q_PROPERTY(QString lastName READ lastName CONSTANT)
//    Q_PROPERTY(int hidden READ hidden CONSTANT)
//    Q_PROPERTY(QString about READ about CONSTANT)
//    Q_PROPERTY(QString activities READ activities CONSTANT)
//    Q_PROPERTY(QString bdate READ bdate CONSTANT)
//    Q_PROPERTY(QString books READ books CONSTANT)
//    Q_PROPERTY(int career_groupId READ career_groupId CONSTANT)
//    Q_PROPERTY(QString career_company READ career_company CONSTANT)
//    Q_PROPERTY(int career_countryId READ career_countryId CONSTANT)
//    Q_PROPERTY(int career_cityId READ career_cityId CONSTANT)
//    Q_PROPERTY(QString career_cityName READ career_cityName CONSTANT)
//    Q_PROPERTY(int career_from READ career_from CONSTANT)
//    Q_PROPERTY(int career_until READ career_until CONSTANT)
//    Q_PROPERTY(QString career_position READ career_position CONSTANT)
//    Q_PROPERTY(int city_id READ city_id CONSTANT)
//    Q_PROPERTY(QString city_title READ city_title CONSTANT)
//    Q_PROPERTY(int commonCount READ commonCount CONSTANT)
//    Q_PROPERTY(QString contacts_mobilePhone READ contacts_mobilePhone CONSTANT)
//    Q_PROPERTY(QString contacts_homePhone READ contacts_homePhone CONSTANT)
//    Q_PROPERTY(int albumsCounter READ albumsCounter CONSTANT)
//    Q_PROPERTY(int videosCounter READ videosCounter CONSTANT)
//    Q_PROPERTY(int audiosCounter READ audiosCounter CONSTANT)
//    Q_PROPERTY(int photosCounter READ photosCounter CONSTANT)
//    Q_PROPERTY(int notesCounter READ notesCounter CONSTANT)
//    Q_PROPERTY(int friendsCounter READ friendsCounter CONSTANT)
//    Q_PROPERTY(int groupsCounter READ groupsCounter CONSTANT)
//    Q_PROPERTY(int onlineFriendsCounter READ onlineFriendsCounter CONSTANT)
//    Q_PROPERTY(int mutualFriendsCounter READ mutualFriendsCounter CONSTANT)
//    Q_PROPERTY(int followersCounter READ followersCounter CONSTANT)
//    Q_PROPERTY(int followersCounter READ followersCounter CONSTANT)
//    Q_PROPERTY(int pagesCounter READ pagesCounter CONSTANT)
//    Q_PROPERTY(int country_id READ country_id CONSTANT)
//    Q_PROPERTY(QString country_title READ country_title CONSTANT)
//    Q_PROPERTY(int education_university READ education_university CONSTANT)
//    Q_PROPERTY(QString education_universityName READ education_universityName CONSTANT)
//    Q_PROPERTY(int education_faculty READ education_faculty CONSTANT)
//    Q_PROPERTY(QString education_facultyName READ education_facultyName CONSTANT)
//    Q_PROPERTY(int education_graduation READ education_graduation CONSTANT)

//    Q_PROPERTY(QString status READ status CONSTANT)
//    Q_PROPERTY(bool online READ online CONSTANT)
//    Q_PROPERTY(QString photo50 READ photo50 CONSTANT)
//    Q_PROPERTY(QString photo200 READ photo200 CONSTANT)
//    Q_PROPERTY(int relation READ relation CONSTANT)
//    Q_PROPERTY(int relationPartnerId READ relationPartnerId CONSTANT)
//    Q_PROPERTY(QString relationPartnerName READ relationPartnerName CONSTANT)
//    Q_PROPERTY(int sex READ sex CONSTANT)

public:
    explicit User(QObject *parent = 0);
    static User* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    QString deactivated() const;
    void setDeactivated(const QString &deactivated);

    bool blacklisted() const;
    void setBlacklisted(bool blacklisted);

    bool blacklistedByMe() const;
    void setBlacklistedByMe(bool blacklistedByMe);

    bool canPost() const;
    void setCanPost(bool canPost);

    bool canSeeAllPosts() const;
    void setCanSeeAllPosts(bool canSeeAllPosts);

    bool canSeeAudio() const;
    void setCanSeeAudio(bool canSeeAudio);

    bool canSendFriendRequest() const;
    void setCanSendFriendRequest(bool canSendFriendRequest);

    bool canWritePrivateMessage() const;
    void setCanWritePrivateMessage(bool canWritePrivateMessage);

    QString domain() const;
    void setDomain(const QString &domain);

    int friendStatus() const;
    void setFriendStatus(int friendStatus);

    bool isFavorite() const;
    void setIsFavorite(bool isFavorite);

    bool isHiddenFromFeed() const;
    void setIsHiddenFromFeed(bool isHiddenFromFeed);

    QString photoMaxOrig() const;
    void setPhotoMaxOrig(const QString &photoMaxOrig);

    bool getVerified() const;
    void setVerified(bool value);

private:
    // System
    int _id = 0;
    QString _deactivated = "";
    bool _blacklisted = false;
    bool _blacklistedByMe = false;
    bool _canPost = false;
    bool _canSeeAllPosts = false;
    bool _canSeeAudio = false;
    bool _canSendFriendRequest = false;
    bool _canWritePrivateMessage = false;
    QString _domain = "";
//    T<?> _exports = nullptr;
    int _friendStatus = 0;
    bool _isFavorite = false;
    bool _isHiddenFromFeed = false;
    QString _photoMaxOrig = "";
    bool verified = false;
};

#endif // USER_H
