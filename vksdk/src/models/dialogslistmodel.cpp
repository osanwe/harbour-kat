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
    int profileId = dialog->lastMessage()->userId();
    int chatId = dialog->lastMessage()->chatId();

    switch (role) {
    case AvatarRole:
        if (dialog->isChat()) return QVariant();
        else {
            if (!_profiles.contains(profileId)) return QVariant();
            return QVariant(_profiles[profileId]->photo50());
        }

    case TitleRole:
        if (dialog->isChat()) return QVariant();
        else {
            if (!_profiles.contains(profileId)) return QVariant();
            return QVariant(_profiles[profileId]->firstName() + " " + _profiles[profileId]->lastName());
        }

    case PreviewRole:
        return QVariant(dialog->lastMessage()->body());

    case IdRole:
        if (dialog->isChat()) return QVariant(dialog->lastMessage()->chatId());
        return QVariant(dialog->lastMessage()->userId());

    case IsChatRole:
        return QVariant(dialog->isChat());

    case UnreadRole:
        return QVariant(dialog->unread());

    case IsOutRole:
        return QVariant(dialog->lastMessage()->out());

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DialogsListModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[AvatarRole] = "avatar";
    roles[TitleRole] = "dialogTitle";
    roles[PreviewRole] = "preview";
    roles[IdRole] = "id";
    roles[IsChatRole] = "isChat";
    roles[UnreadRole] = "unread";
    roles[IsOutRole] = "isOut";
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

void DialogsListModel::addProfile(Friend *profile) {
    if (_profiles.contains(profile->id())) return;
    _profiles[profile->id()] = profile;

    qDebug() << profile->firstName();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

