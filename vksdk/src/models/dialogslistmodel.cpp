#include "dialogslistmodel.h"

DialogsListModel::DialogsListModel(QObject *parent) : QAbstractListModel(parent)
{}

int DialogsListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return _dialogsIds.size();
}

QVariant DialogsListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    Dialog *dialog = _dialogs[_dialogsIds.at(index.row())];

    switch (role) {
    case AvatarRole:
        return QVariant();
    case TitleRole:
        return QVariant();
    case PreviewRole:
        return QVariant(dialog->lastMessage()->body());
    case IdRole:
        if (dialog->isChat()) return QVariant(dialog->lastMessage()->chatId());
        return QVariant(dialog->lastMessage()->userId());
    case IsChatRole:
        return QVariant(dialog->isChat());
    case UnreadRole:
        return QVariant(dialog->unread());
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

void DialogsListModel::add(Dialog *dialog) {
    int id = dialog->isChat() ? dialog->lastMessage()->chatId() : dialog->lastMessage()->userId();
    if (_dialogs.contains(id)) return;

    beginInsertRows(QModelIndex(), _dialogsIds.size(), _dialogsIds.size());
    _dialogsIds.append(id);
    _dialogs[id] = dialog;
    endInsertRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

