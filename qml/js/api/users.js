/*
  Copyright (C) 2015 Petr Vytovtov
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

.pragma library
.import "request.js" as RequestAPI
.import "../storage.js" as StorageJS

var signaller = Qt.createQmlObject("import QtQuick 2.0; \
    QtObject { \
        signal endLoading; \
        signal gotDialogInfo(int dialogId, var info); \
        signal gotUserAvatar(string avatar); \
        signal gotUserNameAndAvatar(string userName, string avatar); \
    }", Qt.application, "UsersSignaller");

// -------------- API functions --------------

function api_getUserNameAndAvatar(uid) {
    RequestAPI.sendRequest("users.get",
                           { user_ids: uid,
                             fields:   "photo_100" },
                           callback_getUserNameAndAvatar)
}

function api_getUserAvatar(uid) {
    RequestAPI.sendRequest("users.get",
                           { user_ids: uid,
                             fields:   "photo_100" },
                           callback_getUserAvatar)
}

function api_getUsersAvatarAndOnlineStatus(uid) {
    RequestAPI.sendRequest("users.get",
                           { user_ids: uid,
                             fields:   "photo_100,online,last_seen" },
                           callback_getUsersAvatarAndOnlineStatus)
}

// -------------- Callbacks --------------

function callback_getUserNameAndAvatar(jsonObject) {
    var firstName = jsonObject.response[0].first_name
    var secondName = jsonObject.response[0].last_name
    var fullName = firstName + " " + secondName
    var oldAvatarName = StorageJS.readUserAvatar()
    var newAvatarName = jsonObject.response[0].photo_100.split("/")
    newAvatarName = newAvatarName[newAvatarName.length - 1]

    if (StorageJS.readFullUserName() !== fullName) {
        console.log("Replacing user name...")
        StorageJS.saveUserName(firstName, secondName)
        signaller.gotUserNameAndAvatar(fullName, cachePath + oldAvatarName)
    }
    if (oldAvatarName !== newAvatarName) {
        console.log("Replacing user avatar...")
        fileDownloader.startDownload(jsonObject.response[0].photo_100, 0)
        StorageJS.saveUserAvatar(newAvatarName)
    }
}

function callback_getUserAvatar(jsonObject) {
    for (var index in jsonObject.response)
        signaller.gotUserAvatar(jsonObject.response[index].photo_100)
}

function callback_getUsersAvatarAndOnlineStatus(jsonObject) {
    for (var index in jsonObject.response) {
        var res = jsonObject.response[index]
        var fullname = res.first_name + " " + res.last_name

        var lastSeenTime = "";
        var lastSeen = res.last_seen
        if (typeof lastSeen !== 'undefined') {
            var date = new Date()
            date.setTime(parseInt(lastSeen.time) * 1000)
            lastSeenTime = ("0" + date.getHours()).slice(-2) + ":" +
                           ("0" + date.getMinutes()).slice(-2) + ", " +
                           ("0" + date.getDate()).slice(-2) + "." +
                           ("0" + (date.getMonth() + 1)).slice(-2) + "." +
                           ("0" + date.getFullYear()).slice(-2)
        }

        StorageJS.saveAnotherUserInfo(res.id,
                                      res.first_name,
                                      res.last_name,
                                      res.photo_100.split('/').slice(-1))
        signaller.gotDialogInfo(res.id,
                                { "avatarSource": res.photo_100,
                                  "nameOrTitle":  fullname,
                                  "isOnline":    (res.online === 1),
                                  "lastSeen":     lastSeenTime })
    }
    signaller.endLoading()
}

// -------------- Other functions --------------

