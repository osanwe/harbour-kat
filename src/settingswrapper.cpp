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
