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

    // requests:
    _friends = new Friends(this);
    _messages = new Messages(this);
    _newsfeed = new Newsfeed(this);
    _photos = new Photos(this);
    _users = new Users(this);
    _wall = new Wall(this);
    _friends->setApi(_api);
    _messages->setApi(_api);
    _newsfeed->setApi(_api);
    _photos->setApi(_api);
    _users->setApi(_api);
    _wall->setApi(_api);
    qRegisterMetaType<Friends*>("Friends*");
    qRegisterMetaType<Messages*>("Messages*");
    qRegisterMetaType<Newsfeed*>("Newsfeed*");
    qRegisterMetaType<Photos*>("Photos*");
    qRegisterMetaType<Users*>("Users*");
    qRegisterMetaType<Wall*>("Wall*");

    // objects:
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

//    _likes = new Likes(this);
//    _longPoll = new LongPoll(this);
//    _videos = new Videos(this);

//    qRegisterMetaType<Audio*>("Audio*");
//    qRegisterMetaType<Document*>("Document*");
//    qRegisterMetaType<News*>("News*");
//    qRegisterMetaType<Photo*>("Photo*");
//    qRegisterMetaType<Friend*>("Friend*");
//    qRegisterMetaType<Video*>("Video*");

//    qRegisterMetaType<Likes*>("Likes*");
//    qRegisterMetaType<LongPoll*>("LongPoll*");
//    qRegisterMetaType<Videos*>("Videos*");
}

VkSDK::~VkSDK() {
    delete _api;
    delete _auth;

    delete _friends;
    delete _messages;
    delete _newsfeed;
    delete _photos;
    delete _users;
    delete _wall;

    delete _dialogsListModel;
    delete _friendsListModel;
    delete _messagesModel;
    delete _newsfeedModel;

//    delete _selfProfile;

//    delete _likes;
//    delete _longPoll;
//    delete _videos;
}

void VkSDK::setAccessTocken(QString value) {
    _api->setAccessToken(value);
}

void VkSDK::setUserId(int value) {
    _userId = value;
}

Authorization *VkSDK::auth() const {
    return _auth;
}

Friends *VkSDK::friends() const {
    return _friends;
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
        emit gotProfile(parseUserProfile(value.toArray()));
        break;
    case ApiRequest::USERS_GET_FRIENDS:
        parseFriendsInfo(value.toArray());
        break;
    case ApiRequest::WALL_GET_BY_ID:
        emit gotWallpost(parseWallpost(value.toObject().value("items").toArray()));
        break;
    default:
        break;
    }
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
        if (dialog->isChat()) _chatsIds.append(QString::number(dialog->lastMessage()->chatId()));
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

News *VkSDK::parseWallpost(QJsonArray array) {
    return array.size() == 1 ? News::fromJsonObject(array.at(0).toObject()) : new News();
}

//User *VkSDK::selfProfile() const {
//    return _selfProfile;
//}

//Likes *VkSDK::likes() const
//{
//    return _likes;
//}

//LongPoll *VkSDK::longPoll() const {
//    return _longPoll;
//}

//Videos *VkSDK::videos() const
//{
//    return _videos;
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

