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

#ifndef MESSAGESMODEL_H
#define MESSAGESMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "../objects/friend.h"
#include "../objects/message.h"

class MessagesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int size READ size CONSTANT)

public:
    enum Roles {
        AvatarRole = Qt::UserRole + 1,
        FromIdRole,
        DateRole,
        IsOutRole,
        IsReadRole,
        BodyRole,
        PhotosRole,
        VideosRole,
        AudiosRole,
        DocumentsRole,
        LinksRole,
        NewsRole,
        GeoTileRole,
        GeoMapRole,
        FwdMessagesRole,
        IdRole,
    };

    explicit MessagesModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void clear();
    Q_INVOKABLE void add(Message *message);
    Q_INVOKABLE void addToBegin(Message *message);
    Q_INVOKABLE void addProfile(Friend *profile);
    Q_INVOKABLE void readMessages(qint64 peerId, qint64 localId, bool out);

    int size() const;

private:
    QList<Message*> _messages;
    QHash<int, Friend*> _profiles;
};

#endif // MESSAGESMODEL_H
