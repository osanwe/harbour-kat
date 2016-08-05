#include "vksdk.h"

VkSDK::VkSDK(QObject *parent) : QObject(parent) {
    _longPoll = new LongPoll(this);
    _messages = new Messages(this);
    _users = new Users(this);

    connect(_messages, SIGNAL(gotChatsList(QList<QObject*>)), this, SLOT(gotChatsList(QList<QObject*>)));
    connect(_messages, SIGNAL(gotDialogsList(QList<QObject*>)), this, SLOT(gotDialogList(QList<QObject*>)));
    connect(_users, SIGNAL(gotUsersList(QList<QObject*>)), this, SLOT(gotUsersList(QList<QObject*>)));

    qRegisterMetaType<LongPoll*>("LongPoll*");
    qRegisterMetaType<Messages*>("Messages*");
    qRegisterMetaType<Users*>("Users*");
}

VkSDK::~VkSDK() {
    delete _longPoll;
    delete _messages;
    delete _users;
}

void VkSDK::setAccessTocken(QString value) {
    _accessToken = value;
    _longPoll->setAccessToken(value);
    _messages->setAccessToken(value);
    _users->setAccessToken(value);
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

void VkSDK::gotChatsList(QList<QObject *> chatsList) {
    foreach (Chat *chat, chatsList) {
        foreach (QVariant user, chat->users()) {
            if (!users.contains(user.toString())) users.append(user.toString());
        }
        foreach (Dialog *dialog, _dialogs) {
            if (dialog->isChat() && dialog->lastMessage()->chatId() == chat->id()) {
                dialog->setChat(chat);
            }
        }
    }
    _users->get(users);
}

void VkSDK::gotDialogList(QList<QObject *> dialogsList) {
    _dialogs = dialogsList;
    foreach (Dialog *dialog, dialogsList) {
        if (dialog->isChat()) _chatsIds.append(dialog->lastMessage()->chatId());
        else _usersIds.append(dialog->lastMessage()->userId());
    }
    if (!_chatsIds.isEmpty()) _messages->getChat(_chatsIds);
    else _users->get(_usersIds);
}

void VkSDK::gotUsersList(QList<QObject *> usersList) {
    foreach (User *user, usersList) {
        foreach (Dialog *dialog, _dialogs) {
            if (!dialog->isChat() && dialog->lastMessage()->userId() == user->id()) {
                dialog->setUser(user);
            }
        }
    }
}

