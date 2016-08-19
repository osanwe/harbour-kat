#ifndef FRIENDSLISTMODEL_H
#define FRIENDSLISTMODEL_H

#include <QAbstractListModel>

#include "../objects/friend.h"

class FriendsListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int size READ size CONSTANT)

public:
    enum {
        IdRole = Qt::UserRole + 1,
        AvatarRole,
        NameRole,
        IsOnlineRole,
        StatusRole,
    };

    explicit FriendsListModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void clear();
    Q_INVOKABLE void add(Friend *profile);

    int size() const;

private:
    QList<int> _ids;
    QHash<int, Friend*> _profiles;
};

#endif // FRIENDSLISTMODEL_H
