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

#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent) : QAbstractListModel(parent)
{}

int PlaylistModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return _audios.size();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    switch (role) {
    case DurationRole:
        return QVariant(_audios.at(index.row())->duration());
    case TitleRole:
        return QVariant(_audios.at(index.row())->title());
    case SubtitleRole:
        return QVariant(_audios.at(index.row())->artist());
    case PlayingRole:
        return QVariant(_playingIndex == index.row());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> PlaylistModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[DurationRole] = "_duration";
    roles[TitleRole] = "_title";
    roles[SubtitleRole] = "_subtitle";
    roles[PlayingRole] = "_playing";
    return roles;
}

void PlaylistModel::clear() {
    beginRemoveRows(QModelIndex(), 0, _audios.size());
    _audios.clear();
    _playingIndex = -1;
    endRemoveRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

void PlaylistModel::add(Audio *audio) {
    beginInsertRows(QModelIndex(), _audios.size(), _audios.size());
    _audios.append(audio);
    endInsertRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

void PlaylistModel::setPlayingIndex(int index) {
    _playingIndex = index;
    QModelIndex startIndex = createIndex(0, 0, static_cast<void *>(0));
    QModelIndex endIndex = createIndex(_audios.size(), 0, static_cast<void *>(0));
    emit dataChanged(startIndex, endIndex);
}

