#include "dialogslistmodel.h"

DialogsListModel::DialogsListModel(QObject *parent) : QAbstractListModel(parent)
{}

int DialogsListModel::rowCount(const QModelIndex &parent) const {
    if (!parent.isValid()) return 0;
    return _dialogsData.size();
}

QVariant DialogsListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    switch (role) {
    case AvatarRole:
        return QVariant();
    case TitleRole:
        return QVariant();
    case PreviewRole:
        return QVariant();
    case IdRole:
        return QVariant();
    case IsChatRole:
        return QVariant();
    case UnreadRole:
        return QVariant();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DialogsListModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[AvatarRole] = "avatar";
    roles[TitleRole] = "title";
    roles[PreviewRole] = "preview";
    roles[IdRole] = "id";
    roles[IsChatRole] = "isChat";
    roles[UnreadRole] = "unread";
    return roles;
}

void DialogsListModel::add(Dialog dialog) {
    beginInsertRows(QModelIndex(), _dialogsData.size(), _dialogsData.size());
    _dialogsData.append(dialog);
    endInsertRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

