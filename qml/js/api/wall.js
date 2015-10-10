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


// -------------- API functions --------------

function api_getPostById(oid, pid) {
    RequestAPI.sendRequest("wall.getById",
                           { posts: oid + "_" + pid },
                           callback_getPostById)
}

function api_post(isGroup, ownerId, message, attachments) {
    if (ownerId !== 0) {
        RequestAPI.sendRequest("wall.post",
                               { owner_id: isGroup ? "-" + ownerId : ownerId,
                                 from_group: 1,
                                 message: message,
                                 attachment: attachments},
                               callback_post)
    } else {
        RequestAPI.sendRequest("wall.post",
                               { message: message,
                                 attachment: attachments},
                               callback_post)
    }
}


// -------------- Callbacks --------------

function callback_getPostById(jsonObject) {
    var item = jsonObject.response[0]
    update(parsePost(item))
}

function callback_post(jsonObject) {
    notificationHelper.sendNotification("", qsTr("Опубликовано"), true);
}


// -------------- Other functions --------------

function parsePost(jsonObject) {
    var postData = []

    var date = new Date()
    date.setTime(parseInt(jsonObject.date) * 1000)

    postData[0] = jsonObject.id
    postData[1] = jsonObject.text.replace(/(https?:\/\/[^\s<]+)/g, "<a href=\"$1\">$1</a>")
    postData[1] = postData[1].replace(/\n/g, "<br>")
    postData[2] = ("0" + date.getHours()).slice(-2) + ":" +
                     ("0" + date.getMinutes()).slice(-2) + ", " +
                     ("0" + date.getDate()).slice(-2) + "." +
                     ("0" + (date.getMonth() + 1)).slice(-2) + "." +
                     ("0" + date.getFullYear()).slice(-2)

//    if (jsonObject.source_id > 0) {
//        for (var index1 in jsonProfiles) {
//            if (jsonProfiles[index1].id === jsonObject.source_id) {
//                console.log(jsonProfiles[index1].photo_100)
//                postData[3] = jsonProfiles[index1].photo_100
//                postData[4] = jsonProfiles[index1].first_name + " " + jsonProfiles[index1].last_name
//            }
//        }
//    } else {
//        var sourceId = Math.abs(jsonObject.source_id)
//        for (var index2 in jsonGroups) {
//            if (jsonGroups[index2].id === sourceId) {
//                console.log(jsonGroups[index2].photo_100)
//                postData[3] = jsonGroups[index2].photo_100
//                postData[4] = jsonGroups[index2].name
//            }
//        }
//    }
//    console.log(postData[4])

    if (jsonObject.attachments) {
        for (var index in jsonObject.attachments) {
            postData[postData.length] = jsonObject.attachments[index]
        }
    }

    return postData
}
