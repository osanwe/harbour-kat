#ifndef DIALOGSLISTMODEL_H
#define DIALOGSLISTMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "../objects/chat.h"
#include "../objects/dialog.h"
#include "../objects/friend.h"

#include <QDebug>

class DialogsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        AvatarRole = Qt::UserRole + 1,
        TitleRole,
        PreviewRole,
        IdRole,
        IsChatRole,
        UnreadRole,
        IsOutRole,
        IsOnlineRole,
        HasAttachmentsRole,
    };

    explicit DialogsListModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void add(Dialog *dialog);
    Q_INVOKABLE void addProfile(Friend *profile);
    Q_INVOKABLE void addChat(Chat *chat);

private:
    QList<int> _dialogsIds;
    QHash<int, Chat*> _chats;
    QHash<int, Dialog*> _dialogs;
    QHash<int, Friend*> _profiles;
};

#endif // DIALOGSLISTMODEL_H
