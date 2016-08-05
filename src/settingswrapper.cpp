#include "settingswrapper.h"

SettingsWrapper::SettingsWrapper(QObject *parent) : QObject(parent) {
    _settings = new QSettings("harbour-kat.conf", QSettings::NativeFormat);
}

SettingsWrapper::~SettingsWrapper() {
    delete _settings;
}

void SettingsWrapper::setAccessToken(QString value) {
    _settings->setValue(ACCESS_TOKEN_KEY, value);
}

void SettingsWrapper::setDefaultPage(QString value) {
    _settings->setValue(DEFAULT_PAGE_KEY, value);
}

QString SettingsWrapper::accessToken() {
    return _settings->value(ACCESS_TOKEN_KEY).toString();
}

QString SettingsWrapper::defaultPage() {
    return _settings->value(DEFAULT_PAGE_KEY).toString();
}
