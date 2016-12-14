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

#include <QtConcurrent/QtConcurrent>
#include <QObject>

#include "authorization.h"
#include "longpoll.h"
#include "objects/group.h"
#include "objects/news.h"
#include "objects/user.h"
#include "objects/video.h"
#include "models/commentsmodel.h"
#include "models/dialogslistmodel.h"
#include "models/friendslistmodel.h"
#include "models/groupslistmodel.h"
#include "models/messagesmodel.h"
#include "models/newsfeedmodel.h"
#include "requests/apirequest.h"
#include "requests/audios.h"
#include "requests/friends.h"
#include "requests/groups.h"
#include "requests/likes.h"
#include "requests/messages.h"
#include "requests/newsfeed.h"
#include "requests/photos.h"
#include "requests/stats.h"
#include "requests/users.h"
#include "requests/videos.h"
#include "requests/wall.h"

//#include "objects/audio.h"
//#include "objects/chat.h"
//#include "objects/dialog.h"
//#include "objects/document.h"
//#include "objects/group.h"
//#include "objects/photo.h"
//#include "objects/friend.h"

class VkSDK : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Authorization* auth READ auth CONSTANT)
    Q_PROPERTY(LongPoll* longPoll READ longPoll CONSTANT)

    Q_PROPERTY(Audios* audios READ audios CONSTANT)
    Q_PROPERTY(Friends* friends READ friends CONSTANT)
    Q_PROPERTY(Groups* groups READ groups CONSTANT)
    Q_PROPERTY(Likes* likes READ likes CONSTANT)
    Q_PROPERTY(Messages* messages READ messages CONSTANT)
    Q_PROPERTY(Newsfeed* newsfeed READ newsfeed CONSTANT)
    Q_PROPERTY(Photos* photos READ photos CONSTANT)
    Q_PROPERTY(Stats* stats READ stats CONSTANT)
    Q_PROPERTY(Users* users READ users CONSTANT)
    Q_PROPERTY(Videos* videos READ videos CONSTANT)
    Q_PROPERTY(Wall* wall READ wall CONSTANT)

    Q_PROPERTY(CommentsModel* commentsModel READ commentsModel CONSTANT)
    Q_PROPERTY(DialogsListModel* dialogsListModel READ dialogsListModel CONSTANT)
    Q_PROPERTY(FriendsListModel* friendsListModel READ friendsListModel CONSTANT)
    Q_PROPERTY(GroupsListModel* groupsListModel READ groupsListModel CONSTANT)
    Q_PROPERTY(MessagesModel* messagesModel READ messagesModel CONSTANT)
    Q_PROPERTY(NewsfeedModel* newsfeedModel READ newsfeedModel CONSTANT)
    Q_PROPERTY(NewsfeedModel* wallModel READ wallModel CONSTANT)

//    Q_PROPERTY(User* selfProfile READ selfProfile CONSTANT)


public:
    explicit VkSDK(QObject *parent = 0);
    ~VkSDK();

    Q_INVOKABLE void setAccessTocken(QString value);
    Q_INVOKABLE void setUserId(int value);

    Authorization *auth() const;
    LongPoll* longPoll() const;

    Audios* audios() const;
    Friends* friends() const;
    Groups* groups() const;
    Likes *likes() const;
    Messages* messages() const;
    Newsfeed* newsfeed() const;
    Photos* photos() const;
    Stats* stats() const;
    Users* users() const;
    Videos* videos() const;
    Wall* wall() const;

    CommentsModel* commentsModel() const;
    DialogsListModel* dialogsListModel() const;
    FriendsListModel* friendsListModel() const;
    GroupsListModel* groupsListModel() const;
    MessagesModel* messagesModel() const;
    NewsfeedModel* newsfeedModel() const;
    NewsfeedModel* wallModel() const;

    Q_INVOKABLE void attachPhotoToMessage(QString path);

//    User* selfProfile() const;

signals:
    void commentCreated();
    void gotGroup(Group *grp);
    void gotNewMessage(QString name, QString preview);
    void gotProfile(User *user);
    void gotUnreadCounter(int value);
    void gotVideo(Video *video);
    void gotUserAudios(QVariantList audios);
    void gotWallpost(News *wallpost);
    void savedPhoto(QString name);
    void gotStats(QList<int> data);
    void userTyping(int userId, int chatId);
//    void gotSelfProfile();
    //    void gotFriends(QVariant friends);
//    void gotMessages(QVariant messages);
//    void newsfeedModelChanged();

public slots:
    void gotResponse(QJsonValue value, ApiRequest::TaskType type);
    void _gotNewMessage(int id);
    void _readMessages(qint64 peerId, qint64 localId, bool out);
    void _userTyping(qint64 userId, qint64 chatId);

//    void gotDialogList(QList<Dialog*> dialogsList);
//    void gotFriendsList(QList<QObject*> friendsList);
//    void gotMessagesList(QList<QObject*> messagesList);
//    void gotMutualFriendsIds(QVariantList ids);
//    void gotNewsfeed(QList<News*> items, QList<User*> profiles, QList<Group *> groups, QString nextFrom);
//    void gotUnreadDialogsCounter(int value);
//    void gotUserProfile(User *user);
//    void gotUsersList(QList<QObject*> usersList);
//    void gotVideoObject(Video *video);
//    void gotWallpostObject(News *wallpost);

//    void gotChatsList(QList<QObject*> chatsList);

private:
    QString _accessToken;
    int _userId;

    ApiRequest *_api;
    Authorization *_auth;
    LongPoll *_longPoll;

    Audios *_audios;
    Friends *_friends;
    Groups *_groups;
    Likes *_likes;
    Messages *_messages;
    Newsfeed *_newsfeed;
    Photos *_photos;
    Stats *_stats;
    Users *_users;
    Videos *_videos;
    Wall *_wall;

    CommentsModel *_commentsModel;
    DialogsListModel *_dialogsListModel;
    FriendsListModel *_friendsListModel;
    GroupsListModel *_groupsListModel;
    MessagesModel *_messagesModel;
    NewsfeedModel *_newsfeedModel;
    NewsfeedModel *_wallModel;

    QString _messagePreview;
    QString _pathToPhoto;
    QStringList _chatUsersIds;
    QStringList _usersIds;
    QStringList _chatsIds;

    void parseAudiosList(QJsonArray array);
    void parseChatsInfo(QJsonArray array);
    void parseComments(QJsonObject object);
    void parseDialogsInfo(QJsonObject object);
    void parseEntireFriendsList(QJsonArray array);
    void parseFriendsInfo(QJsonArray array);
    void parseGroupsList(QJsonArray array);
    void parseLimitedFriendsList(QJsonArray array);
    void parseMessages(QJsonArray array);
    void parseNewMessage(QJsonObject object);
    void parseNewsfeed(QJsonObject object, bool isWall);
    void parseSavedPhotoData(QJsonArray array);
    void parseStatistics(QJsonArray array);
    void parseUploadedPhotoData(QJsonObject object);
    void parseUploadServerData(QJsonObject object);
    User* parseUserProfile(QJsonArray array);
    Video* parseVideoInfo(QJsonArray array);
    News* parseWallpost(QJsonArray array);

//    User *_selfProfile;

//    QList<QObject*> _dialogs;

//    QStringList _getIdsFromMessages(QList<QObject*> messages);
};

#endif // VKSDK_H
