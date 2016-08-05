#ifndef CHAT_H
#define CHAT_H

#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QVariantList>

class Chat : public QObject
{
    Q_OBJECT
public:
    explicit Chat(QObject *parent = 0);

    const Chat* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    QString title() const;
    void setTitle(const QString &title);

    QString photo() const;
    void setPhoto(const QString &photo);

    QVariantList users() const;
    void setUsers(const QVariantList &users);

private:
    int _id;
    QString _title;
    QString _photo;
    QVariantList _users;
};

#endif // CHAT_H
