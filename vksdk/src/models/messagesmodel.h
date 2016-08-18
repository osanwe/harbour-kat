#ifndef MESSAGESMODEL_H
#define MESSAGESMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "../objects/friend.h"
#include "../objects/message.h"

class MessagesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int size READ size CONSTANT)

public:
    enum Roles {
        AvatarRole = Qt::UserRole + 1,
        IdRole,
        DateRole,
        IsOutRole,
        IsReadRole,
        BodyRole,
        PhotosRole,
        VideosRole,
        AudiosRole,
        DocumentsRole,
        NewsRole,
        GeoTileRole,
        GeoMapRole,
        FwdMessagesRole,
    };

    explicit MessagesModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void clear();
    Q_INVOKABLE void add(Message *message);
    Q_INVOKABLE void addProfile(Friend *profile);

    int size() const;

private:
    QList<Message*> _messages;
    QHash<int, Friend*> _profiles;
};

#endif // MESSAGESMODEL_H
