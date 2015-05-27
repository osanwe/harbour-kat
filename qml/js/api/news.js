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

function api_getLastNews(startFrom) {
    var query = "newsfeed.get?v=5.13"
    query += "&filters=post"
    query += "&return_banned=0"
    if (startFrom) query += "&start_from" + startFrom
    RequestAPI.sendRequest(query, callback_getLastNews)
}


// -------------- Callbacks --------------

function callback_getLastNews(jsonObject) {
    for (var index in jsonObject.response.items) {
        appendPostToNewsFeed(parsePost(jsonObject.response.items[index]))
    }
}


// -------------- Other functions --------------

function parsePost(jsonObject) {
    var postData = []

    var date = new Date()
    date.setTime(parseInt(jsonObject.date) * 1000)

    postData[0] = jsonObject.post_id
    postData[1] = jsonObject.text.replace(/(https?:\/\/[^\s<]+)/g, "<a href=\"$1\">$1</a>")
    postData[2] = ("0" + date.getHours()).slice(-2) + ":" +
                     ("0" + date.getMinutes()).slice(-2) + ", " +
                     ("0" + date.getDate()).slice(-2) + "." +
                     ("0" + (date.getMonth() + 1)).slice(-2) + "." +
                     ("0" + date.getFullYear()).slice(-2)

    if (jsonObject.attachments) {
        for (var index in jsonObject.attachments) {
            postData[postData.length] = jsonObject.attachments[index]
        }
    }


//    if (jsonObject.fwd_messages) {
//        for (var index in jsonObject.fwd_messages) {
//            postData[messageData.length] = jsonObject.fwd_messages[index]
//        }
//    }

//    if (jsonObject.geo) {
//        postData[messageData.length] = jsonObject.geo
//    }

    return postData
}
