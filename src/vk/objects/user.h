#ifndef USER_H
#define USER_H

#include <QJsonObject>
#include <QObject>
#include <QString>

#include <QDebug>

class User : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QString firstName READ firstName CONSTANT)
    Q_PROPERTY(QString lastName READ lastName CONSTANT)
    Q_PROPERTY(QString status READ status CONSTANT)
    Q_PROPERTY(QString bdate READ bdate CONSTANT)
    Q_PROPERTY(QString city READ city CONSTANT)
    Q_PROPERTY(bool online READ online CONSTANT)
    Q_PROPERTY(QString photo50 READ photo50 CONSTANT)
    Q_PROPERTY(QString photo200 READ photo200 CONSTANT)
    Q_PROPERTY(QString photoMaxOrig READ photoMaxOrig CONSTANT)
    Q_PROPERTY(int relation READ relation CONSTANT)
    Q_PROPERTY(int relationPartnerId READ relationPartnerId CONSTANT)
    Q_PROPERTY(QString relationPartnerName READ relationPartnerName CONSTANT)
    Q_PROPERTY(int sex READ sex CONSTANT)
    Q_PROPERTY(bool verified READ verified CONSTANT)
    Q_PROPERTY(int videosCounter READ videosCounter CONSTANT)
    Q_PROPERTY(int audiosCounter READ audiosCounter CONSTANT)
    Q_PROPERTY(int photosCounter READ photosCounter CONSTANT)
    Q_PROPERTY(int notesCounter READ notesCounter CONSTANT)
    Q_PROPERTY(int groupsCounter READ groupsCounter CONSTANT)
    Q_PROPERTY(int pagesCounter READ pagesCounter CONSTANT)
    Q_PROPERTY(int friendsCounter READ friendsCounter CONSTANT)
    Q_PROPERTY(int onlineFriendsCounter READ onlineFriendsCounter CONSTANT)
    Q_PROPERTY(int mutualFriendsCounter READ mutualFriendsCounter CONSTANT)
    Q_PROPERTY(int followersCounter READ followersCounter CONSTANT)

public:
    explicit User(QObject *parent = 0);

    static User* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    QString firstName() const;
    void setFirstName(const QString &firstName);

    QString lastName() const;
    void setLastName(const QString &lastName);

    QString status() const;
    void setStatus(const QString &status);

    QString bdate() const;
    void setBdate(const QString &bdate);

    QString city() const;
    void setCity(const QString &city);

    bool online() const;
    void setOnline(int online);

    QString photo50() const;
    void setPhoto50(const QString &photo50);

    QString photo200() const;
    void setPhoto200(const QString &photo200);

    QString photoMaxOrig() const;
    void setPhotoMaxOrig(const QString &photoMaxOrig);

    int relation() const;
    void setRelation(int relation);

    int sex() const;
    void setSex(int sex);

    bool verified() const;
    void setVerified(bool verified);

    int videosCounter() const;
    void setVideosCounter(int videosCounter);

    int audiosCounter() const;
    void setAudiosCounter(int audiosCounter);

    int photosCounter() const;
    void setPhotosCounter(int photosCounter);

    int notesCounter() const;
    void setNotesCounter(int notesCounter);

    int groupsCounter() const;
    void setGroupsCounter(int groupsCounter);

    int pagesCounter() const;
    void setPagesCounter(int pagesCounter);

    int friendsCounter() const;
    void setFriendsCounter(int friendsCounter);

    int onlineFriendsCounter() const;
    void setOnlineFriendsCounter(int onlineFriendsCounter);

    int mutualFriendsCounter() const;
    void setMutualFriendsCounter(int mutualFriendsCounter);

    int followersCounter() const;
    void setFollowersCounter(int followersCounter);

    int relationPartnerId() const;
    void setRelationPartnerId(int relationPartnerId);

    QString relationPartnerName() const;
    void setRelationPartnerName(const QString &relationPartnerName);

private:
    int _id;
    QString _firstName;
    QString _lastName;
    QString _bdate;
    QString _city;
    bool _online;
    QString _photo50;
    QString _photo200;
    QString _photoMaxOrig;
    int _relation;
    int _relationPartnerId;
    QString _relationPartnerName;
    int _sex;
    QString _status;
    bool _verified;
    int _videosCounter = 0;
    int _audiosCounter = 0;
    int _photosCounter = 0;
    int _notesCounter = 0;
    int _groupsCounter = 0;
    int _pagesCounter = 0;
    int _friendsCounter = 0;
    int _onlineFriendsCounter = 0;
    int _mutualFriendsCounter = 0;
    int _followersCounter = 0;
};

#endif // USER_H
