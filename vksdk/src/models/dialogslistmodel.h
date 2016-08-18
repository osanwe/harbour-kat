#ifndef DIALOGSLISTMODEL_H
#define DIALOGSLISTMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "../objects/dialog.h"

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
    };

    explicit DialogsListModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void add(Dialog *dialog);

private:
    QList<int> _dialogsIds;
    QHash<int, Dialog*> _dialogs;
};

#endif // DIALOGSLISTMODEL_H
