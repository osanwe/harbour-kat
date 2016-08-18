#ifndef MESSAGESMODEL_H
#define MESSAGESMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "../objects/message.h"

class MessagesModel : public QAbstractListModel
{
    Q_OBJECT
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

private:
    QList<Message*> _messages;
};

#endif // MESSAGESMODEL_H
