#ifndef GROUP_H
#define GROUP_H

#include <QJsonObject>
#include <QObject>
#include <QString>

#include <QDebug>

class Group : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString photo50 READ photo50 CONSTANT)
    Q_PROPERTY(QString photo100 READ photo100 CONSTANT)
    Q_PROPERTY(QString photo200 READ photo200 CONSTANT)

public:
    explicit Group(QObject *parent = 0);

    static Group* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString photo50() const;
    void setPhoto50(const QString &photo50);

    QString photo100() const;
    void setPhoto100(const QString &photo100);

    QString photo200() const;
    void setPhoto200(const QString &photo200);

private:
    int _id;
    QString _name;
    QString _photo50;
    QString _photo100;
    QString _photo200;
};

#endif // GROUP_H
