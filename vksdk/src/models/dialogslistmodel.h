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

    Q_PROPERTY(qint64 size READ size CONSTANT)

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        AvatarRole,
        TitleRole,
        PreviewRole,
        UnreadRole,
        IsChatRole,
        IsOnlineRole,
        IsOutRole,
    };

    explicit DialogsListModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void add(Dialog *dialog);
    Q_INVOKABLE void addProfile(Friend *profile);
    Q_INVOKABLE void addChat(Chat *chat);
    Q_INVOKABLE void readMessages(qint64 peerId, qint64 localId, bool out);
    Q_INVOKABLE void update(Message *message);

    qint64 size() const;

private:
    QList<qint64> _dialogsIds;
    QHash<qint64, Chat*> _chats;
    QHash<qint64, Dialog*> _dialogs;
    QHash<qint64, Friend*> _profiles;
};

#endif // DIALOGSLISTMODEL_H
