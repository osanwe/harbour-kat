#include "vksdk.h"

VkSDK::VkSDK(QObject *parent) : QObject(parent) {
    _longPoll = new LongPoll(this);
    _messages = new Messages(this);

    qRegisterMetaType<LongPoll*>("LongPoll*");
    qRegisterMetaType<Messages*>("Messages*");
}

VkSDK::~VkSDK() {
    delete _longPoll;
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

