#ifndef USER_H
#define USER_H

#include <QJsonObject>
#include <QObject>
#include <QString>

class User : public QObject
{
    Q_OBJECT

public:
    explicit User(QObject *parent = 0);

    static User* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    QString firstName() const;
    void setFirstName(const QString &firstName);

    QString lastName() const;
    void setLastName(const QString &lastName);

    QString photo() const;
    void setPhoto(const QString &photo);

    QString status() const;
    void setStatus(const QString &status);

    bool isOnline() const;
    void setIsOnline(bool isOnline);

private:
    int _id;
    QString _firstName;
    QString _lastName;
    QString _photo;
    QString _status;
    bool _isOnline;
};

#endif // USER_H
