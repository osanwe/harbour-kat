#include "vksdk.h"

VkSDK::VkSDK(QObject *parent) : QObject(parent)
{}

VkSDK::~VkSDK()
{}

void VkSDK::setAccessTocken(QString value) {
    _accessToken = value;
}

