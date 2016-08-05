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

#ifndef SETTINGSWRAPPER_H
#define SETTINGSWRAPPER_H

#include <QObject>
#include <QSettings>
#include <QString>

class SettingsWrapper : public QObject
{
    Q_OBJECT

public:
    explicit SettingsWrapper(QObject *parent = 0);
    ~SettingsWrapper();

    Q_INVOKABLE void setAccessToken(QString value);
    Q_INVOKABLE void setUserId(int value);
    Q_INVOKABLE void setDefaultPage(QString value);

    Q_INVOKABLE QString accessToken();
    Q_INVOKABLE int userId();
    Q_INVOKABLE QString defaultPage();

    Q_INVOKABLE void removeAccessToken();
    Q_INVOKABLE void removeUserId();

private:
    QSettings *_settings;

    const QString ACCESS_TOKEN_KEY = "accessToken";
    const QString USER_ID_KEY = "userId";
    const QString DEFAULT_PAGE_KEY = "defaultPage";
};

#endif // SETTINGSWRAPPER_H
