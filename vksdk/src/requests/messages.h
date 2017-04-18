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

#ifndef MESSAGES_H
#define MESSAGES_H

#include "requestbase.h"

class Messages : public RequestBase
{
    Q_OBJECT

public:
    explicit Messages(QObject *parent = 0);

    Q_INVOKABLE void getById(int id);
    Q_INVOKABLE void getChat(const QStringList &ids);
    Q_INVOKABLE void getDialogs(int offset = 0);
    Q_INVOKABLE void getHistory(int peerId, int offset = 0);
    Q_INVOKABLE void markAsRead(int peerId);
    Q_INVOKABLE void send(int peerId, const QString &text, const QString &attachmentsList);
    Q_INVOKABLE void setActivity(int peerId);
};

#endif // MESSAGES_H
