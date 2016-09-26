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

#ifndef NEWSFEEDMODEL_H
#define NEWSFEEDMODEL_H

#include <QAbstractListModel>
//#include <QObject>
//#include <QList>

#include "../objects/group.h"
#include "../objects/news.h"
#include "../objects/user.h"

//#include <QDebug>

class NewsfeedModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int size READ size CONSTANT)
    Q_PROPERTY(QString next READ next CONSTANT)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(int id READ id WRITE setId)

public:
    enum Roles {
        AvatarRole = Qt::UserRole + 1,
        TitleRole,
        TextRole,
        DateRole,
        CommentsCountRole,
        LikesCountRole,
        RepostsCountRole,
        IsLikedRole,
        IsRepostedRole,
        AttachmentsRole,
        FullPostRole,
        PostIdRole,
        SourceIdRole,
    };

    explicit NewsfeedModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames() const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    Q_INVOKABLE void clear();
    Q_INVOKABLE void addGroup(Group *group);
    Q_INVOKABLE void addNews(News *news);
    Q_INVOKABLE void addUser(User *user);
    Q_INVOKABLE void setNextFrom(QString value);

    int size() const;
    QString next() const;

    int count() const;
    void setCount(int count);

    int id() const;
    void setId(int id);

signals:
    void countChanged();

private:
    QList<News *> _newsfeed;
    QHash<int, User*> _profiles;
    QHash<int, Group*> _groups;
    QString _nextFrom;
    int _count = 0;
    int _id = 0;

    QString _getAvatarSource(const int id) const;
    QString _getTitle(const int id) const;
};

#endif // NEWSFEEDMODEL_H
