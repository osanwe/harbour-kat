#include "vksdk.h"

VkSDK::VkSDK(QObject *parent) : QObject(parent) {
    _longPoll = new LongPoll(this);

    qRegisterMetaType<LongPoll*>("LongPoll*");
}

VkSDK::~VkSDK() {
    delete _longPoll;
}

void VkSDK::setAccessTocken(QString value) {
    _accessToken = value;
    _longPoll->setAccessToken(value);
}

LongPoll *VkSDK::longPoll() const {
    return _longPoll;
}

