#ifndef FRIEND_H
#define FRIEND_H

#include <QJsonObject>
#include <QObject>
#include <QString>

class Friend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QString firstName READ firstName CONSTANT)
    Q_PROPERTY(QString lastName READ lastName CONSTANT)
    Q_PROPERTY(QString photo50 READ photo50 CONSTANT)
    Q_PROPERTY(bool online READ online CONSTANT)
    Q_PROPERTY(QString status READ status CONSTANT)

public:
    explicit Friend(QObject *parent = 0);

    static Friend* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    QString firstName() const;
    void setFirstName(const QString &firstName);

    QString lastName() const;
    void setLastName(const QString &lastName);

    QString photo50() const;
    void setPhoto50(const QString &photo50);

    bool online() const;
    void setOnline(bool online);

    QString status() const;
    void setStatus(const QString &status);

private:
    int _id;
    QString _firstName;
    QString _lastName;
    QString _photo50;
    bool _online;
    QString _status;
};

#endif // FRIEND_H
