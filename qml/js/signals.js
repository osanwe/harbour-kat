/*
  Copyright (C) 2015 Albert Shteiner
  Contact: Albert Shteiner <ckazzku@gmail.com>
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

.pragma library

var jsSignaller = Qt.createQmlObject("import QtQuick 2.0; \
    QtObject { \
        signal endLoading; \
        signal gotChatUsers(var users); \
        signal gotDialogInfo(int dialogId, var info); \
        signal gotDialogs(var dialogs); \
        signal gotHistory(var messages); \
        signal gotMessageInfo(int userId, var info); \
        signal gotNewMessage(var message); \
        signal gotSearchDialogs(int id, string name, string photo, bool isOnline); \
        signal gotUnreadCount(int count); \
        signal gotUserAvatar(string avatar); \
        signal gotUserNameAndAvatar(string userName, string avatar); \
        signal needScrollToBottom; \
    }", Qt.application, "JSSignaller");
