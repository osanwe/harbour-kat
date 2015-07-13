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

.import "request.js" as RequestAPI
.import "../storage.js" as StorageJS


// -------------- API functions --------------

function api_getUserNameAndAvatar(uid) {
    RequestAPI.sendRequest("users.get", null, {
                               user_ids: uid,
                               fields: "photo_100"
                           }, callback_getUserNameAndAvatar)
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
        updateUserNameAndAvatar(fullName, "/home/nemo/.cache/harbour-kat/" + oldAvatarName)
    }
    if (oldAvatarName !== newAvatarName) {
        console.log("Replacing user avatar...")
        fileDownloader.startDownload(jsonObject.response[0].photo_100, 0)
        StorageJS.saveUserAvatar(newAvatarName)
    }
}


// -------------- Other functions --------------

function getUserAvatar(uid) {
    var url = "https://api.vk.com/method/"
    url += "users.get?"
    url += "user_ids=" + uid
    url += "&fields=photo_100"
    url += "&access_token=" + StorageJS.readSettingsValue("access_token")
    console.log(url)

    var doc = new XMLHttpRequest()
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            console.log(doc.responseText)
            var jsonObject = JSON.parse(doc.responseText)
            for (var index in jsonObject.response) {
                setUserAvatar(jsonObject.response[index].photo_100)
            }
        }
    }
    doc.open("GET", url, true)
    doc.send()
}

function getUsersAvatarAndOnlineStatus(uid) {
    var url = "https://api.vk.com/method/"
    url += "users.get?"
    url += "user_ids=" + uid
    url += "&fields=photo_100,online"
    url += "&access_token=" + StorageJS.readSettingsValue("access_token")
    console.log(url)

    var doc = new XMLHttpRequest()
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            console.log(doc.responseText)
            var jsonObject = JSON.parse(doc.responseText)
            for (var index in jsonObject.response) {
                var fullname = jsonObject.response[index].first_name + " " +
                        jsonObject.response[index].last_name
                updateDialogsList(index,
                                  jsonObject.response[index].photo_100,
                                  fullname,
                                  jsonObject.response[index].online)
            }
            stopBusyIndicator()
        }
    }
    doc.open("GET", url, true)
    doc.send()
}
