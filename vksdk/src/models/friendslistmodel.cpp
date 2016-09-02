/*
  Copyright (C) 2016 Petr Vytovtov
  Contact: Petr Vytovtov <osanwe@protonmail.ch>
  All rights reserved.

  This file is part of Kat.

  Kat is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Kat is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Kat.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    qDeleteAll(_profiles);
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

