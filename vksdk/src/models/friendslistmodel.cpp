#include "friendslistmodel.h"

FriendsListModel::FriendsListModel(QObject *parent) : QAbstractListModel(parent)
{}

int FriendsListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return _ids.size();
}

QVariant FriendsListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    Friend *profile = _profiles[_ids.at(index.row())];

    switch (role) {
    case IdRole:
        return QVariant(profile->id());
    case AvatarRole:
        return QVariant(profile->photo50());
    case NameRole:
        return QVariant(QString("%1 %2").arg(profile->firstName()).arg(profile->lastName()));
    case IsOnlineRole:
        return QVariant(profile->online());
    case StatusRole:
        return QVariant(profile->status());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> FriendsListModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[IdRole] = "id";
    roles[AvatarRole] = "avatar";
    roles[NameRole] = "name";
    roles[IsOnlineRole] = "online";
    roles[StatusRole] = "status";
    return roles;
}

void FriendsListModel::clear() {
    beginRemoveRows(QModelIndex(), 0, _ids.size());
    _ids.clear();
    _profiles.clear();
    endRemoveRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

void FriendsListModel::add(Friend *profile) {
    if (_profiles.contains(profile->id())) return;

    beginInsertRows(QModelIndex(), _ids.size(), _ids.size());
    _ids.append(profile->id());
    _profiles[profile->id()] = profile;
    endInsertRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

int FriendsListModel::size() const {
    return _ids.size();
}

