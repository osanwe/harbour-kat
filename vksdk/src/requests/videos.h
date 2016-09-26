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

#ifndef VIDEOS_H
#define VIDEOS_H

//#include <QJsonArray>
//#include <QJsonObject>
//#include <QJsonValue>
#include <QObject>
//#include <QString>

#include "apirequest.h"
//#include "objects/video.h"

class Videos : public QObject
{
    Q_OBJECT

public:
    explicit Videos(QObject *parent = 0);
    ~Videos();

    Q_INVOKABLE void get(int ownerId, int videoId);

    void setApi(ApiRequest *api);

private:
    ApiRequest *_api;
};

#endif // VIDEOS_H
