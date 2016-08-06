#include "vksdk.h"

VkSDK::VkSDK(QObject *parent) : QObject(parent) {
    _friends = new Friends(this);
    _longPoll = new LongPoll(this);
    _messages = new Messages(this);
    _users = new Users(this);

    connect(_friends, SIGNAL(gotFriendsList(QList<QObject*>)), this, SLOT(gotFriendsList(QList<QObject*>)));
    connect(_messages, SIGNAL(gotChatsList(QList<QObject*>)), this, SLOT(gotChatsList(QList<QObject*>)));
    connect(_messages, SIGNAL(gotDialogsList(QList<QObject*>)), this, SLOT(gotDialogList(QList<QObject*>)));
    connect(_users, SIGNAL(gotUserProfile(User*)), this, SLOT(gotUserProfile(User*)));

    qRegisterMetaType<Friend*>("Friend*");
    qRegisterMetaType<User*>("User*");

    qRegisterMetaType<Friends*>("Friends*");
    qRegisterMetaType<LongPoll*>("LongPoll*");
    qRegisterMetaType<Messages*>("Messages*");
    qRegisterMetaType<Users*>("Users*");
}

VkSDK::~VkSDK() {
    delete _selfProfile;

    delete _friends;
    delete _longPoll;
    delete _messages;
    delete _users;
}

void VkSDK::setAccessTocken(QString value) {
    _accessToken = value;
    _friends->setAccessToken(value);
    _longPoll->setAccessToken(value);
    _messages->setAccessToken(value);
    _users->setAccessToken(value);
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

LongPoll *VkSDK::longPoll() const {
    return _longPoll;
}

Messages *VkSDK::messages() const {
    return _messages;
}

Users *VkSDK::users() const {
    return _users;
}

void VkSDK::gotFriendsList(QList<QObject *> friendsList) {
    emit gotFriends(QVariant::fromValue(friendsList));
}

void VkSDK::gotUserProfile(User *user) {
    if (user->id() == _userId) {
        _selfProfile = user;
        emit gotSelfProfile();
        emit gotProfile(user);
    } else emit gotProfile(user);
}

void VkSDK::gotChatsList(QList<QObject *> chatsList) {
//    foreach (Chat *chat, chatsList) {
//        foreach (QVariant user, chat->users()) {
////            if (!users.contains(user.toString())) users.append(user.toString());
//        }
//        foreach (Dialog *dialog, _dialogs) {
//            if (dialog->isChat() && dialog->lastMessage()->chatId() == chat->id()) {
//                dialog->setChat(chat);
//            }
//        }
//    }
//    _users->get(users);
}

void VkSDK::gotDialogList(QList<QObject *> dialogsList) {
//    _dialogs = dialogsList;
//    foreach (Dialog *dialog, dialogsList) {
////        if (dialog->isChat()) _chatsIds.append(dialog->lastMessage()->chatId());
////        else _usersIds.append(dialog->lastMessage()->userId());
//    }
//    if (!_chatsIds.isEmpty()) _messages->getChat(_chatsIds);
//    else _users->get(_usersIds);
}

void VkSDK::gotUsersList(QList<QObject *> usersList) {
//    foreach (User *user, usersList) {
//        foreach (Dialog *dialog, _dialogs) {
//            if (!dialog->isChat() && dialog->lastMessage()->userId() == user->id()) {
//                dialog->setUser(user);
//            }
//        }
//    }
}

