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

#ifndef VKSDK_H
#define VKSDK_H

#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantList>

#include "friends.h"
#include "longpoll.h"
#include "messages.h"
#include "users.h"
#include "videos.h"
#include "objects/audio.h"
#include "objects/chat.h"
#include "objects/dialog.h"
#include "objects/document.h"
#include "objects/photo.h"
#include "objects/friend.h"
#include "objects/user.h"
#include "objects/video.h"

class VkSDK : public QObject
{
    Q_OBJECT

    Q_PROPERTY(User* selfProfile READ selfProfile CONSTANT)

    Q_PROPERTY(Friends* friends READ friends CONSTANT)
    Q_PROPERTY(LongPoll* longPoll READ longPoll CONSTANT)
    Q_PROPERTY(Messages* messages READ messages CONSTANT)
    Q_PROPERTY(Users* users READ users CONSTANT)
    Q_PROPERTY(Videos* videos READ videos CONSTANT)

public:
    explicit VkSDK(QObject *parent = 0);
    ~VkSDK();

    Q_INVOKABLE void setAccessTocken(QString value);
    Q_INVOKABLE void setUserId(int value);

    User* selfProfile() const;

    Friends* friends() const;
    LongPoll* longPoll() const;
    Messages* messages() const;
    Users* users() const;
    Videos* videos() const;

signals:
    void gotFriends(QVariant friends);
    void gotMessages(QVariant messages);
    void gotSelfProfile();
    void gotProfile(User *user);
    void gotVideo(Video *video);

public slots:
    void gotFriendsList(QList<QObject*> friendsList);
    void gotMessagesList(QList<QObject*> messagesList);
    void gotMutualFriendsIds(QVariantList ids);
    void gotUserProfile(User *user);
    void gotUsersList(QList<QObject*> usersList);
    void gotVideoObject(Video *video);

    void gotChatsList(QList<QObject*> chatsList);
    void gotDialogList(QList<QObject*> dialogsList);

private:
    QString _accessToken;
    int _userId;
    User *_selfProfile;

    Friends *_friends;
    LongPoll *_longPoll;
    Messages *_messages;
    Users *_users;
    Videos *_videos;

    QStringList _usersIds;
    QStringList _chatsIds;
    QList<QObject*> _dialogs;

    QStringList _getIdsFromMessages(QList<QObject*> messages);
};

#endif // VKSDK_H
