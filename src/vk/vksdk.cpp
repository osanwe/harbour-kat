#include "vksdk.h"

VkSDK::VkSDK(QObject *parent) : QObject(parent) {
    _longPoll = new LongPoll(this);
    _messages = new Messages(this);
    _users = new Users(this);

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

