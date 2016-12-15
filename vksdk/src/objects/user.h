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

    // Basic info
    Q_PROPERTY(QString firstName READ getFirstName CONSTANT)
    Q_PROPERTY(QString nickname READ getNickname CONSTANT)
    Q_PROPERTY(QString lastName READ getLastName CONSTANT)
    Q_PROPERTY(QString maidenName READ getMaidenName CONSTANT)
    Q_PROPERTY(bool online READ getOnline CONSTANT)
    Q_PROPERTY(QString photo50 READ getPhoto50 CONSTANT)
    Q_PROPERTY(QString photo200 READ getPhoto200 CONSTANT)
    Q_PROPERTY(QString status READ getStatus CONSTANT)
    Q_PROPERTY(int lastSeenTime READ getLastSeenTime CONSTANT)
    Q_PROPERTY(int lastSeenPlatform READ getLastSeenPlatform CONSTANT)
    Q_PROPERTY(QString bdate READ getBdate CONSTANT)
    Q_PROPERTY(int relation READ getRelation CONSTANT)
    Q_PROPERTY(int relationPartnerId READ getRelationPartnerId CONSTANT)
    Q_PROPERTY(QString relationPartnerFirstName READ getRelationPartnerFirstName CONSTANT)
    Q_PROPERTY(QString relationPartnerLastName READ getRelationPartnerLastName CONSTANT)
    Q_PROPERTY(QString occupationType READ getOccupationType CONSTANT)
    Q_PROPERTY(int occupationId READ getOccupationId CONSTANT)
    Q_PROPERTY(QString occupationName READ getOccupationName CONSTANT)
    // --------------
    Q_PROPERTY(int sex READ getSex CONSTANT)
    Q_PROPERTY(int cityId READ getCityId CONSTANT)
    Q_PROPERTY(QString cityTitle READ getCityTitle() CONSTANT)
    Q_PROPERTY(int countryId READ getCountryId CONSTANT)
    Q_PROPERTY(QString countryTitle READ getCountryTitle CONSTANT)
    Q_PROPERTY(QString homeTown READ getHomeTown CONSTANT)
    Q_PROPERTY(QString contactsMobilePhone READ getContactsMobilePhone CONSTANT)
    Q_PROPERTY(QString contactsHomePhone READ getContactsHomePhone CONSTANT)
    Q_PROPERTY(QString site READ getSite CONSTANT)

    // Buttons
    Q_PROPERTY(int counterFriends READ getCounterFriends CONSTANT)
    Q_PROPERTY(int counterPhotos READ getCounterPhotos CONSTANT)
    Q_PROPERTY(int counterVideos READ getCounterVideos CONSTANT)
    Q_PROPERTY(int counterAudios READ getCounterAudios CONSTANT)
    Q_PROPERTY(int counterGroups READ getCounterGroups CONSTANT)
    Q_PROPERTY(int counterNotes READ getCounterNotes CONSTANT)
    // --------------
    Q_PROPERTY(int counterAlbums READ getCounterAlbums CONSTANT)
    Q_PROPERTY(int counterOnlineFriends READ getCounterOnlineFriends CONSTANT)
    Q_PROPERTY(int counterMutualFriends READ getCounterMutualFriends CONSTANT)
    Q_PROPERTY(int counterUserVideos READ getCounterUserVideos CONSTANT)
    Q_PROPERTY(int counterFollowers READ getCounterFollowers CONSTANT)
    Q_PROPERTY(int counterPages READ getCounterPages CONSTANT)

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
//    Q_PROPERTY(int commonCount READ commonCount CONSTANT)
//    Q_PROPERTY(int education_university READ education_university CONSTANT)
//    Q_PROPERTY(QString education_universityName READ education_universityName CONSTANT)
//    Q_PROPERTY(int education_faculty READ education_faculty CONSTANT)
//    Q_PROPERTY(QString education_facultyName READ education_facultyName CONSTANT)
//    Q_PROPERTY(int education_graduation READ education_graduation CONSTANT)

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

    QString getFirstName() const;
    void setFirstName(const QString &firstName);

    QString getNickname() const;
    void setNickname(const QString &nickname);

    QString getLastName() const;
    void setLastName(const QString &lastName);

    QString getMaidenName() const;
    void setMaidenName(const QString &maidenName);

    bool getOnline() const;
    void setOnline(bool value);

    QString getPhoto50() const;
    void setPhoto50(const QString &photo50);

    QString getPhoto200() const;
    void setPhoto200(const QString &photo200);

    QString getStatus() const;
    void setStatus(const QString &status);

    int getLastSeenTime() const;
    void setLastSeenTime(int value);

    int getLastSeenPlatform() const;
    void setLastSeenPlatform(int value);

    QString getBdate() const;
    void setBdate(const QString &bdate);

    int getRelation() const;
    void setRelation(int relation);

    int getRelationPartnerId() const;
    void setRelationPartnerId(int value);

    QString getRelationPartnerFirstName() const;
    void setRelationPartnerFirstName(const QString &value);

    QString getRelationPartnerLastName() const;
    void setRelationPartnerLastName(const QString &value);

    QString getOccupationType() const;
    void setOccupationType(const QString &value);

    int getOccupationId() const;
    void setOccupationId(int value);

    QString getOccupationName() const;
    void setOccupationName(const QString &value);

    int getCounterFriends() const;
    void setCounterFriends(int counterFriends);

    int getCounterPhotos() const;
    void setCounterPhotos(int counterPhotos);

    int getCounterVideos() const;
    void setCounterVideos(int counterVideos);

    int getCounterAudios() const;
    void setCounterAudios(int counterAudios);

    int getCounterGroups() const;
    void setCounterGroups(int counterGroups);

    int getCounterNotes() const;
    void setCounterNotes(int counterNotes);

    int getCounterAlbums() const;
    void setCounterAlbums(int counterAlbums);

    int getCounterOnlineFriends() const;
    void setCounterOnlineFriends(int counterOnlineFriends);

    int getCounterMutualFriends() const;
    void setCounterMutualFriends(int counterMutualFriends);

    int getCounterUserVideos() const;
    void setCounterUserVideos(int counterUserVideos);

    int getCounterFollowers() const;
    void setCounterFollowers(int counterFollowers);

    int getCounterPages() const;
    void setCounterPages(int counterPages);

    int getSex() const;
    void setSex(int sex);

    int getCityId() const;
    void setCityId(int cityId);

    QString getCityTitle() const;
    void setCityTitle(const QString &cityTitle);

    int getCountryId() const;
    void setCountryId(int countryId);

    QString getCountryTitle() const;
    void setCountryTitle(const QString &countryTitle);

    QString getHomeTown() const;
    void setHomeTown(const QString &homeTown);

    QString getContactsMobilePhone() const;
    void setContactsMobilePhone(const QString &contactsMobilePhone);

    QString getContactsHomePhone() const;
    void setContactsHomePhone(const QString &contactsHomePhone);

    QString getSite() const;
    void setSite(const QString &site);

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

    // Basic info
    QString _firstName = "";
    QString _nickname = "";
    QString _lastName = "";
    QString _maidenName = "";
    bool _online = false;
    QString _photo50 = "";
    QString _photo200 = "";
    QString _status = "";
    int _lastSeenTime = 0;
    int _lastSeenPlatform = 0;
    QString _bdate = "";
    int _relation = 0;
    int _relationPartnerId = 0;
    QString _relationPartnerFirstName = "";
    QString _relationPartnerLastName = "";
    QString _occupationType = "";
    int _occupationId = 0;
    QString _occupationName = "";
    // --------------
    int _sex = 0;
    int _cityId = 0;
    QString _cityTitle = "";
    int _countryId = 0;
    QString _countryTitle = "";
    QString _homeTown = "";
    QString _contactsMobilePhone = "";
    QString _contactsHomePhone = "";
    QString _site = "";

    // Buttons
    int _counterFriends = 0;
    int _counterPhotos = 0;
    int _counterVideos = 0;
    int _counterAudios = 0;
    int _counterGroups = 0;
    int _counterNotes = 0;
    // --------------
    int _counterAlbums = 0;
    int _counterOnlineFriends = 0;
    int _counterMutualFriends = 0;
    int _counterUserVideos = 0;
    int _counterFollowers = 0;
    int _counterPages = 0;
};

#endif // USER_H
