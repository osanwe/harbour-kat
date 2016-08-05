#ifndef USER_H
#define USER_H

#include <QJsonObject>
#include <QObject>
#include <QString>

class User : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QString firstName READ firstName CONSTANT)
    Q_PROPERTY(QString lastName READ lastName CONSTANT)
    Q_PROPERTY(QString status READ status CONSTANT)
    Q_PROPERTY(QString bdate READ bdate CONSTANT)
    Q_PROPERTY(QString city READ city CONSTANT)
    Q_PROPERTY(int online READ online CONSTANT)
    Q_PROPERTY(QString photo50 READ photo50 CONSTANT)
    Q_PROPERTY(QString photoMaxOrig READ photoMaxOrig CONSTANT)
    Q_PROPERTY(int relation READ relation CONSTANT)
    Q_PROPERTY(int sex READ sex CONSTANT)
    Q_PROPERTY(bool verified READ verified CONSTANT)

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
    void setOnline(bool online);

    QString photo50() const;
    void setPhoto50(const QString &photo50);

    QString photoMaxOrig() const;
    void setPhotoMaxOrig(const QString &photoMaxOrig);

    int relation() const;
    void setRelation(int relation);

    int sex() const;
    void setSex(int sex);

    bool verified() const;
    void setVerified(bool verified);

private:
    int _id;
    QString _firstName;
    QString _lastName;
    QString _bdate;
    QString _city;
    // TODO: Add counters
    bool _online;
    QString _photo50;
    QString _photoMaxOrig;
    int _relation;
    int _sex;
    QString _status;
    bool _verified;
};

#endif // USER_H
