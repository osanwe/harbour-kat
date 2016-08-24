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
    // basic:
    _api = new ApiRequest(this);
    _auth = new Authorization(this);
    qRegisterMetaType<Authorization*>("Authorization*");
    connect(_api, SIGNAL(gotResponse(QJsonValue,ApiRequest::TaskType)),
            this, SLOT(gotResponse(QJsonValue,ApiRequest::TaskType)));

    _longPoll = new LongPoll(this);
    connect(_longPoll, SIGNAL(gotNewMessage(int)), this, SLOT(_gotNewMessage(int)));
    connect(_longPoll, SIGNAL(readMessages(qint64,qint64,bool)), this, SLOT(_readMessages(qint64,qint64,bool)));
    connect(_longPoll, SIGNAL(userTyping(qint64,qint64)), this, SLOT(_userTyping(qint64,qint64)));

    // requests:
    _friends = new Friends(this);
    _likes = new Likes(this);
    _messages = new Messages(this);
    _newsfeed = new Newsfeed(this);
    _photos = new Photos(this);
    _users = new Users(this);
    _videos = new Videos(this);
    _wall = new Wall(this);
//    _longPoll->setApi(_api);
    _friends->setApi(_api);
    _likes->setApi(_api);
    _messages->setApi(_api);
    _newsfeed->setApi(_api);
    _photos->setApi(_api);
    _users->setApi(_api);
    _videos->setApi(_api);
    _wall->setApi(_api);
    qRegisterMetaType<LongPoll*>("LongPoll*");
    qRegisterMetaType<Friends*>("Friends*");
    qRegisterMetaType<Likes*>("Likes*");
    qRegisterMetaType<Messages*>("Messages*");
    qRegisterMetaType<Newsfeed*>("Newsfeed*");
    qRegisterMetaType<Photos*>("Photos*");
    qRegisterMetaType<Users*>("Users*");
    qRegisterMetaType<Videos*>("Videos*");
    qRegisterMetaType<Wall*>("Wall*");

    // objects:
    qRegisterMetaType<News*>("News*");
    qRegisterMetaType<User*>("User*");

    //models:
    _dialogsListModel = new DialogsListModel(this);
    _friendsListModel = new FriendsListModel(this);
    _messagesModel = new MessagesModel(this);
    _newsfeedModel = new NewsfeedModel(this);
    qRegisterMetaType<DialogsListModel*>("DialogsListModel*");
    qRegisterMetaType<FriendsListModel*>("FriendsListModel*");
    qRegisterMetaType<MessagesModel*>("MessagesModel*");
    qRegisterMetaType<NewsfeedModel*>("NewsfeedModel*");


//    qRegisterMetaType<Audio*>("Audio*");
//    qRegisterMetaType<Document*>("Document*");
//    qRegisterMetaType<Photo*>("Photo*");
//    qRegisterMetaType<Friend*>("Friend*");
//    qRegisterMetaType<Video*>("Video*");
}

VkSDK::~VkSDK() {
    delete _api;
    delete _auth;
    delete _longPoll;

    delete _friends;
    delete _likes;
    delete _messages;
    delete _newsfeed;
    delete _photos;
    delete _users;
    delete _videos;
    delete _wall;

    delete _dialogsListModel;
    delete _friendsListModel;
    delete _messagesModel;
    delete _newsfeedModel;

//    delete _selfProfile;
}

void VkSDK::setAccessTocken(QString value) {
    _api->setAccessToken(value);
    _longPoll->setAccessToken(value);
}

void VkSDK::setUserId(int value) {
    _userId = value;
}

Authorization *VkSDK::auth() const {
    return _auth;
}

LongPoll *VkSDK::longPoll() const {
    return _longPoll;
}

Friends *VkSDK::friends() const {
    return _friends;
}

Likes *VkSDK::likes() const {
    return _likes;
}

Messages *VkSDK::messages() const {
    return _messages;
}

Photos *VkSDK::photos() const {
    return _photos;
}

Newsfeed *VkSDK::newsfeed() const {
    return _newsfeed;
}

Wall *VkSDK::wall() const {
    return _wall;
}

Users *VkSDK::users() const {
    return _users;
}

Videos *VkSDK::videos() const {
    return _videos;
}

DialogsListModel *VkSDK::dialogsListModel() const {
    return _dialogsListModel;
}

FriendsListModel *VkSDK::friendsListModel() const {
    return _friendsListModel;
}

MessagesModel *VkSDK::messagesModel() const {
    return _messagesModel;
}

NewsfeedModel* VkSDK::newsfeedModel() const {
    return _newsfeedModel;
}

void VkSDK::attachPhotoToMessage(QString path) {
    _pathToPhoto = path;
    _photos->getMessagesUploadServer();
}

void VkSDK::gotResponse(QJsonValue value, ApiRequest::TaskType type) {
    switch (type) {
    case ApiRequest::FRIENDS_GET:
        parseEntireFriendsList(value.toObject().value("items").toArray());
        break;
    case ApiRequest::FRIENDS_GET_MUTUAL:
    case ApiRequest::FRIENDS_GET_ONLINE:
        parseLimitedFriendsList(value.toArray());
        break;
    case ApiRequest::MESSAGES_GET_BY_ID:
        parseNewMessage(value.toObject().value("items").toArray().at(0).toObject());
        break;
    case ApiRequest::MESSAGES_GET_CHAT:
        parseChatsInfo(value.toArray());
        break;
    case ApiRequest::MESSAGES_GET_DIALOGS:
        parseDialogsInfo(value.toObject());
        break;
    case ApiRequest::MESSAGES_GET_HISTORY:
        parseMessages(value.toObject().value("items").toArray());
        break;
    case ApiRequest::PHOTOS_GET_MESSAGES_UPLOAD_SERVER:
        parseUploadServerData(value.toObject());
        break;
    case ApiRequest::PHOTOS_SAVE_MESSAGES_PHOTO:
        parseSavedPhotoData(value.toArray());
        break;
    case ApiRequest::PHOTOS_UPLOAD_TO_SERVER:
        parseUploadedPhotoData(value.toObject());
        break;
    case ApiRequest::NEWSFEED_GET:
        parseNewsfeed(value.toObject());
        break;
    case ApiRequest::USERS_GET:
        if (_messagePreview.isEmpty()) emit gotProfile(parseUserProfile(value.toArray()));
        else {
            emit gotNewMessage(QString("%1 %2").arg(parseUserProfile(value.toArray())->firstName())
                                               .arg(parseUserProfile(value.toArray())->lastName()),
                               _messagePreview);
            _messagePreview.clear();
        }
        break;
    case ApiRequest::USERS_GET_FRIENDS:
        parseFriendsInfo(value.toArray());
        break;
    case ApiRequest::VIDEO_GET:
        emit gotVideo(parseVideoInfo(value.toObject().value("items").toArray()));
        break;
    case ApiRequest::WALL_GET_BY_ID:
        emit gotWallpost(parseWallpost(value.toObject().value("items").toArray()));
        break;
    default:
        break;
    }
}

void VkSDK::_gotNewMessage(int id) {
    _messages->getById(id);
}

void VkSDK::_readMessages(qint64 peerId, qint64 localId, bool out) {
    _dialogsListModel->readMessages(peerId, localId, out);
    _messagesModel->readMessages(peerId, localId, out);
}

void VkSDK::_userTyping(qint64 userId, qint64 chatId) {
    //
}

void VkSDK::parseChatsInfo(QJsonArray array) {
    _chatsIds.clear();
    for (int index = 0; index < array.size(); ++index) {
        Chat *chat = Chat::fromJsonObject(array.at(index).toObject());
        foreach (QVariant user, chat->users()) _usersIds.append(user.toString());
        _dialogsListModel->addChat(chat);
    }
    _usersIds.removeDuplicates();
    _users->getUsersByIds(_usersIds);
}

void VkSDK::parseDialogsInfo(QJsonObject object) {
    if (object.contains("unread_dialogs")) emit gotUnreadCounter(object.value("unread_dialogs").toInt());
    QJsonArray dialogs = object.value("items").toArray();
    for (int index = 0; index < dialogs.size(); ++index) {
        Dialog *dialog = Dialog::fromJsonObject(dialogs.at(index).toObject());
        if (dialog->isChat()) _chatsIds.append(QString::number(dialog->lastMessage()->chatId() - 2000000000));
        else _usersIds.append(QString::number(dialog->lastMessage()->userId()));
        _dialogsListModel->add(dialog);
    }
    if (_chatsIds.empty()) {
        _usersIds.removeDuplicates();
        _users->getUsersByIds(_usersIds);
    } else _messages->getChat(_chatsIds);
}

void VkSDK::parseEntireFriendsList(QJsonArray array) {
    for (int index = 0; index < array.size(); ++index) {
        Friend *profile = Friend::fromJsonObject(array.at(index).toObject());
        _friendsListModel->add(profile);
    }
}

void VkSDK::parseFriendsInfo(QJsonArray array) {
    if (!_usersIds.empty()) {
        _usersIds.clear();
        for (int index = 0; index < array.size(); ++index) {
            Friend *profile = Friend::fromJsonObject(array.at(index).toObject());
            _dialogsListModel->addProfile(profile);
        }
    } else if (!_chatUsersIds.empty()) {
        _chatUsersIds.clear();
        for (int index = 0; index < array.size(); ++index) {
            Friend *profile = Friend::fromJsonObject(array.at(index).toObject());
            _messagesModel->addProfile(profile);
        }
    } else {
        for (int index = 0; index < array.size(); ++index) {
            Friend *profile = Friend::fromJsonObject(array.at(index).toObject());
            _friendsListModel->add(profile);
        }
    }
}

void VkSDK::parseLimitedFriendsList(QJsonArray array) {
    QStringList ids;
    for (int index = 0; index < array.size(); ++index) {
        ids.append(QString::number(array.at(index).toInt()));
    }
    _users->getUsersByIds(ids);
}

void VkSDK::parseMessages(QJsonArray array) {
    for (int index = 0; index < array.size(); ++index) {
        Message *message = Message::fromJsonObject(array.at(index).toObject());
        _chatUsersIds.append(QString::number(message->fromId()));
        foreach (QObject *object, message->fwdMessagesList()) {
            Message *fwd = qobject_cast<Message*>(object);
            _chatUsersIds.append(QString::number(fwd->fromId()));
        }
        _messagesModel->add(message);
    };
    _chatUsersIds.removeDuplicates();
    _users->getUsersByIds(_chatUsersIds);
}

void VkSDK::parseNewMessage(QJsonObject object) {
    Message *message = Message::fromJsonObject(object);
    if (message->chat()) message->setFromId(message->userId());
    else message->setFromId(message->out() ? 0 : message->userId());
    // Update dialogs
    _dialogsListModel->update(message);
    // Update chat
    _messagesModel->addToBegin(message);
    // Show notification
    if (message->out()) return;
    _messagePreview = (message->hasAttachments() ? "[ 📎 ] " : "") + message->body();
    _users->getUserProfile(message->userId());
}

void VkSDK::parseNewsfeed(QJsonObject object) {
    QJsonArray posts = object.value("items").toArray();
    QJsonArray profiles = object.value("profiles").toArray();
    QJsonArray groups = object.value("groups").toArray();
    QString nextFrom = object.value("next_from").toString();
    for (int index = 0; index < posts.size(); ++index) {
        News *post = News::fromJsonObject(posts.at(index).toObject());
        _newsfeedModel->addNews(post);
    }
    for (int index = 0; index < profiles.size(); ++index) {
        User *profile = User::fromJsonObject(profiles.at(index).toObject());
        _newsfeedModel->addUser(profile);
    }
    for (int index = 0; index < groups.size(); ++index) {
        Group *group = Group::fromJsonObject(groups.at(index).toObject());
        _newsfeedModel->addGroup(group);
    }
    _newsfeedModel->setNextFrom(nextFrom);
}

void VkSDK::parseSavedPhotoData(QJsonArray array) {
    QJsonObject photo = array.at(0).toObject();
    emit savedPhoto(QString("photo%1_%2").arg(QString::number(photo.value("owner_id").toInt()))
                                         .arg(QString::number(photo.value("id").toInt())));
}

void VkSDK::parseUploadedPhotoData(QJsonObject object) {
    QString server = QString::number(object.value("server").toInt());
    QString photo = object.value("photo").toString();
    QString hash = object.value("hash").toString();
    _photos->saveMessagesPhoto(photo, server, hash);
}

void VkSDK::parseUploadServerData(QJsonObject object) {
    QString uploadUrl = object.value("upload_url").toString();
    QString albumId = QString::number(object.value("album_id").toInt());
    QString userId = QString::number(object.value("user_id").toInt());
    _photos->uploadPhotoToServer(uploadUrl, albumId, userId, _pathToPhoto);
}

User *VkSDK::parseUserProfile(QJsonArray array) {
    return array.size() == 1 ? User::fromJsonObject(array.at(0).toObject()) : new User();
}

Video *VkSDK::parseVideoInfo(QJsonArray array) {
    return array.size() == 1 ? Video::fromJsonObject(array.at(0).toObject()) : new Video();
}

News *VkSDK::parseWallpost(QJsonArray array) {
    return array.size() == 1 ? News::fromJsonObject(array.at(0).toObject()) : new News();
}

//User *VkSDK::selfProfile() const {
//    return _selfProfile;
//}

//void VkSDK::gotFriendsList(QList<QObject *> friendsList) {
//    emit gotFriends(QVariant::fromValue(friendsList));
//}

//void VkSDK::gotMessagesList(QList<QObject *> messagesList) {
//    foreach (QObject *object, messagesList) {
//        Message *message = qobject_cast<Message*>(object);
//        _messagesModel->add(message);
//        _chatUsersIds.append(QString("%1").arg(message->fromId()));
//    }
//    _users->get(_chatUsersIds);
//}

//void VkSDK::gotMutualFriendsIds(QVariantList ids) {
//    QStringList sIds;
//    foreach (QVariant id, ids) sIds.append(id.toString());
//    _users->get(sIds);
//}

//void VkSDK::gotNewsfeed(QList<News *> items, QList<User *> profiles, QList<Group *> groups, QString nextFrom)
//{
//    foreach (News *item, items) _newsfeedModel->addNews(item);
//    foreach (User *user, profiles) _newsfeedModel->addUser(user);
//    foreach (Group *group, groups) _newsfeedModel->addGroup(group);
//    _newsfeedModel->setNextFrom(nextFrom);
//    //    emit newsfeedModelChanged();
//}

//void VkSDK::gotUnreadDialogsCounter(int value) {
//    emit gotUnreadCounter(value);
//}

//void VkSDK::gotUserProfile(User *user) {
//    if (user->id() == _userId) {
//        _selfProfile = user;
//        emit gotSelfProfile();
//    } else emit gotProfile(user);
//}

//void VkSDK::gotUsersList(QList<QObject *> usersList) {
//    if (_usersIds.size() > 0) {
//        _usersIds.clear();
//        foreach (QObject *object, usersList) {
//            Friend *user = qobject_cast<Friend*>(object);
//            _dialogsListModel->addProfile(user);
//        }
//    } else if (_chatUsersIds.size() > 0) {
//        _chatUsersIds.clear();
//        foreach (QObject *object, usersList) {
//            Friend *user = qobject_cast<Friend*>(object);
//            _messagesModel->addProfile(user);
//        }
//    } else emit gotFriends(QVariant::fromValue(usersList));
//}

//void VkSDK::gotVideoObject(Video *video)
//{
//    emit gotVideo(video);
//}

//void VkSDK::gotWallpostObject(News *wallpost)
//{
//    emit gotWallpost(wallpost);
//}

//void VkSDK::gotChatsList(QList<QObject *> chatsList) {
//    _chatsIds.clear();
//    foreach (QObject *object, chatsList) {
//        Chat *chat = qobject_cast<Chat*>(object);
//        foreach (QVariant user, chat->users()) {
//            if (!_usersIds.contains(user.toString())) _usersIds.append(user.toString());
//        }
//        _dialogsListModel->addChat(chat);
//    }
//    _users->get(_usersIds);
//}

//void VkSDK::gotDialogList(QList<Dialog *> dialogsList) {
//    foreach (Dialog *dialog, dialogsList) {
//        _dialogsListModel->add(dialog);
//        if (dialog->isChat()) _chatsIds.append(QString("%1").arg(dialog->lastMessage()->chatId()));
//        else _usersIds.append(QString("%1").arg(dialog->lastMessage()->userId()));
//    }
//    if (_chatsIds.empty()) _users->get(_usersIds);
//    else _messages->getChat(_chatsIds);
//}

//QStringList VkSDK::_getIdsFromMessages(QList<QObject *> messages) {
//    QStringList ids;
//    for (int index = 0; index < messages.size(); ++index) {
//        Message *msg = qobject_cast<Message*>(messages.at(index));
//        QString id = QString("%1").arg(msg->fromId());
//        if (!ids.contains(id) && id != "0") {
//            ids.append(id);
//        }
//        if (!msg->fwdMessagesList().isEmpty()) ids += _getIdsFromMessages(msg->fwdMessagesList());
//    }
//    return ids;
//}

