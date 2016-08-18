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

#include "vksdk.h"

VkSDK::VkSDK(QObject *parent) : QObject(parent) {
    _friends = new Friends(this);
    _likes = new Likes(this);
    _longPoll = new LongPoll(this);
    _messages = new Messages(this);
    _newsfeed = new Newsfeed(this);
    _users = new Users(this);
    _videos = new Videos(this);
    _wall = new Wall(this);

    _dialogsListModel = new DialogsListModel(this);
    _messagesModel = new MessagesModel(this);
    _newsfeedModel = new NewsfeedModel(this);

    connect(_friends, SIGNAL(gotFriendsList(QList<QObject*>)), this, SLOT(gotFriendsList(QList<QObject*>)));
    connect(_friends, SIGNAL(gotMutualFriendsIds(QVariantList)), this, SLOT(gotMutualFriendsIds(QVariantList)));
    connect(_messages, SIGNAL(gotChatsList(QList<QObject*>)), this, SLOT(gotChatsList(QList<QObject*>)));
    connect(_messages, SIGNAL(gotDialogsList(QList<Dialog*>)), this, SLOT(gotDialogList(QList<Dialog*>)));
    connect(_messages, SIGNAL(gotMessagesList(QList<QObject*>)), this, SLOT(gotMessagesList(QList<QObject*>)));
    connect(_messages, SIGNAL(gotUnreadDialogsCounter(int)), this, SLOT(gotUnreadDialogsCounter(int)));
    connect(_newsfeed, SIGNAL(gotNewsfeed(QList<News*>,QList<User*>,QList<Group*>,QString)), this, SLOT(gotNewsfeed(QList<News*>,QList<User*>,QList<Group*>,QString)));
    connect(_users, SIGNAL(gotUserProfile(User*)), this, SLOT(gotUserProfile(User*)));
    connect(_users, SIGNAL(gotUsersList(QList<QObject*>)), this, SLOT(gotUsersList(QList<QObject*>)));
    connect(_videos, SIGNAL(gotVideo(Video*)), this, SLOT(gotVideoObject(Video*)));
    connect(_wall, SIGNAL(gotWallpost(News*)), this, SLOT(gotWallpostObject(News*)));

    qRegisterMetaType<Audio*>("Audio*");
    qRegisterMetaType<Document*>("Document*");
    qRegisterMetaType<News*>("News*");
    qRegisterMetaType<Photo*>("Photo*");
    qRegisterMetaType<Friend*>("Friend*");
    qRegisterMetaType<User*>("User*");
    qRegisterMetaType<Video*>("Video*");

    qRegisterMetaType<DialogsListModel*>("DialogsListModel*");
    qRegisterMetaType<MessagesModel*>("MessagesModel*");
    qRegisterMetaType<NewsfeedModel*>("NewsfeedModel*");

    qRegisterMetaType<Friends*>("Friends*");
    qRegisterMetaType<Likes*>("Likes*");
    qRegisterMetaType<LongPoll*>("LongPoll*");
    qRegisterMetaType<Messages*>("Messages*");
    qRegisterMetaType<Newsfeed*>("Newsfeed*");
    qRegisterMetaType<Users*>("Users*");
    qRegisterMetaType<Videos*>("Videos*");
    qRegisterMetaType<Wall*>("Wall*");
}

VkSDK::~VkSDK() {
    delete _selfProfile;

    delete _friends;
    delete _likes;
    delete _longPoll;
    delete _messages;
    delete _newsfeed;
    delete _users;
    delete _videos;
    delete _wall;

    delete _dialogsListModel;
    delete _messagesModel;
    delete _newsfeedModel;
}

void VkSDK::setAccessTocken(QString value) {
    _accessToken = value;
    _friends->setAccessToken(value);
    _likes->setAccessToken(value);
    _longPoll->setAccessToken(value);
    _messages->setAccessToken(value);
    _newsfeed->setAccessToken(value);
    _users->setAccessToken(value);
    _videos->setAccessToken(value);
    _wall->setAccessToken(value);
}

void VkSDK::setUserId(int value) {
    _userId = value;
}

User *VkSDK::selfProfile() const {
    return _selfProfile;
}

Friends *VkSDK::friends() const {
    return _friends;
}

Likes *VkSDK::likes() const
{
    return _likes;
}

LongPoll *VkSDK::longPoll() const {
    return _longPoll;
}

Messages *VkSDK::messages() const {
    return _messages;
}

Newsfeed *VkSDK::newsfeed() const {
    return _newsfeed;
}

Users *VkSDK::users() const {
    return _users;
}

Videos *VkSDK::videos() const
{
    return _videos;
}

Wall *VkSDK::wall() const
{
    return _wall;
}

DialogsListModel *VkSDK::dialogsListModel() const {
    return _dialogsListModel;
}

MessagesModel *VkSDK::messagesModel() const {
    return _messagesModel;
}

NewsfeedModel* VkSDK::newsfeedModel() const {
    return _newsfeedModel;
}

void VkSDK::gotFriendsList(QList<QObject *> friendsList) {
    emit gotFriends(QVariant::fromValue(friendsList));
}

void VkSDK::gotMessagesList(QList<QObject *> messagesList) {
    foreach (QObject *object, messagesList) {
        Message *message = qobject_cast<Message*>(object);
        _messagesModel->add(message);
        _chatUsersIds.append(QString("%1").arg(message->fromId()));
    }
    _users->get(_chatUsersIds);
}

void VkSDK::gotMutualFriendsIds(QVariantList ids) {
    QStringList sIds;
    foreach (QVariant id, ids) sIds.append(id.toString());
    _users->get(sIds);
}

void VkSDK::gotNewsfeed(QList<News *> items, QList<User *> profiles, QList<Group *> groups, QString nextFrom)
{
    foreach (News *item, items) _newsfeedModel->addNews(item);
    foreach (User *user, profiles) _newsfeedModel->addUser(user);
    foreach (Group *group, groups) _newsfeedModel->addGroup(group);
    _newsfeedModel->setNextFrom(nextFrom);
    //    emit newsfeedModelChanged();
}

void VkSDK::gotUnreadDialogsCounter(int value) {
    emit gotUnreadCounter(value);
}

void VkSDK::gotUserProfile(User *user) {
    if (user->id() == _userId) {
        _selfProfile = user;
        emit gotSelfProfile();
    } else emit gotProfile(user);
}

void VkSDK::gotUsersList(QList<QObject *> usersList) {
    if (_usersIds.size() > 0) {
        _usersIds.clear();
        foreach (QObject *object, usersList) {
            Friend *user = qobject_cast<Friend*>(object);
            _dialogsListModel->addProfile(user);
        }
    } else if (_chatUsersIds.size() > 0) {
        _chatUsersIds.clear();
        foreach (QObject *object, usersList) {
            Friend *user = qobject_cast<Friend*>(object);
            _messagesModel->addProfile(user);
        }
    } else emit gotFriends(QVariant::fromValue(usersList));
}

void VkSDK::gotVideoObject(Video *video)
{
    emit gotVideo(video);
}

void VkSDK::gotWallpostObject(News *wallpost)
{
    emit gotWallpost(wallpost);
}

void VkSDK::gotChatsList(QList<QObject *> chatsList) {
    _chatsIds.clear();
    foreach (QObject *object, chatsList) {
        Chat *chat = qobject_cast<Chat*>(object);
        foreach (QVariant user, chat->users()) {
            if (!_usersIds.contains(user.toString())) _usersIds.append(user.toString());
        }
        _dialogsListModel->addChat(chat);
    }
    _users->get(_usersIds);
}

void VkSDK::gotDialogList(QList<Dialog *> dialogsList) {
    foreach (Dialog *dialog, dialogsList) {
        _dialogsListModel->add(dialog);
        if (dialog->isChat()) _chatsIds.append(QString("%1").arg(dialog->lastMessage()->chatId()));
        else _usersIds.append(QString("%1").arg(dialog->lastMessage()->userId()));
    }
    if (_chatsIds.empty()) _users->get(_usersIds);
    else _messages->getChat(_chatsIds);
}

QStringList VkSDK::_getIdsFromMessages(QList<QObject *> messages) {
    QStringList ids;
    for (int index = 0; index < messages.size(); ++index) {
        Message *msg = qobject_cast<Message*>(messages.at(index));
        QString id = QString("%1").arg(msg->fromId());
        if (!ids.contains(id) && id != "0") {
            ids.append(id);
        }
        if (!msg->fwdMessagesList().isEmpty()) ids += _getIdsFromMessages(msg->fwdMessagesList());
    }
    return ids;
}

