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

#include "groupslistmodel.h"

GroupsListModel::GroupsListModel(QObject *parent) : QAbstractListModel(parent)
{}

int GroupsListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return _ids.size();
}

QVariant GroupsListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    Group *group = _groups[_ids.at(index.row())];

    switch (role) {
    case IdRole:
        return QVariant(group->id());
    case AvatarRole:
        return QVariant(group->photo50());
    case NameRole:
        return QVariant(group->name());
    case StatusRole:
        return QVariant(group->status());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> GroupsListModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[IdRole] = "id";
    roles[AvatarRole] = "avatar";
    roles[NameRole] = "name";
    roles[StatusRole] = "status";
    return roles;
}

void GroupsListModel::clear() {
    beginRemoveRows(QModelIndex(), 0, _ids.size());
    _ids.clear();
    _groups.clear();
    endRemoveRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

void GroupsListModel::add(Group *group) {
    if (_groups.contains(group->id())) return;

    beginInsertRows(QModelIndex(), _ids.size(), _ids.size());
    _ids.append(group->id());
    _groups[group->id()] = group;
    endInsertRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

int GroupsListModel::size() const {
    return _ids.size();
}
