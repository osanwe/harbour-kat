#include "vksdk.h"

VkSDK::VkSDK(QObject *parent) : QObject(parent) {
    _request = new ApiRequest(this);
}

VkSDK::~VkSDK() {
    delete _request;
}

void VkSDK::setAccessTocken(QString value) {
    _accessToken = value;
}

