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

.import "../storage.js" as StorageJS
.import "request.js" as RequestAPI
.import "users.js" as UsersAPI


// -------------- API functions --------------

function api_getUnreadMessagesCounter(isCover) {
    var query = "messages.getDialogs?v=5.14"
    query += "&unread=1"
    RequestAPI.sendRequest(query, isCover ?
                                  callback_getUnreadMessagesCounter_cover :
                                  callback_getUnreadMessagesCounter_mainMenu)
}

function api_getDialogsList(offset) {
    var query = "messages.getDialogs?v=5.14"
    query += "&offset=" + offset
    RequestAPI.sendRequest(query, callback_getDialogsList)
}

function api_getHistory(isChat, dialogId, offset) {
    var query = "messages.getHistory?v=5.14"
    query += (isChat ? "&chat_id=" : "&user_id=") + dialogId
    query += "&offset=" + offset
    query += "&count=50"
    RequestAPI.sendRequest(query, callback_getHistory)
}

function api_sendMessage(isChat, dialogId, message, isNew) {
    var query = "messages.send?v=5.14"
    query += (isChat ? "&chat_id=" : "&user_id=") + dialogId
    query += "&message=" + message
    RequestAPI.sendRequest(query, callback_sendMessage)
}

function api_createChat(ids, message) {
    var query = "messages.createChat?v=5.14"
    query += "&user_ids=" + ids
    query += "&title=" + message
    RequestAPI.sendRequest(query, callback_createChat)
}

function api_searchDialogs(substring) {
    var query = "messages.searchDialogs?v=5.14"
    query += "&q=" + substring
    query += "&fields=photo_100,online"
    RequestAPI.sendRequest(query, callback_searchDialogs)
}

function api_markDialogAsRead(isChat, uid, mid) {
    var query = "messages.markAsRead?v=5.14"
    query += "&peer_id=" + uid
    query += "&start_message_id=" + mid
    RequestAPI.sendRequest(query)
}

function api_getChatUsers(dialogId) {
    var query = "messages.getChatUsers?v=5.14"
    query += "&chat_id=" + dialogId
    query += "&fields=online,photo_100,status"
    RequestAPI.sendRequest(query, callback_getChatUsers)
}


// -------------- Callbacks --------------

function callback_getUnreadMessagesCounter_mainMenu(jsonObject) {
    updateUnreadMessagesCounter(jsonObject.response.count)
}

function callback_getUnreadMessagesCounter_cover(jsonObject) {
    updateCoverCounters(jsonObject.response.count)
}

function callback_getDialogsList(jsonObject) {
    var uids = ""
    var chatsUids = ""
    var items = jsonObject.response.items
    for (var index in items) {
        var jsonMessage = items[index].message

        var dialogId = jsonMessage.user_id
        var messageBody = jsonMessage.body
        var isChat = false
        if (jsonMessage.fwd_messages)
            messageBody = "[сообщения] " + messageBody
        if (jsonMessage.attachments)
            messageBody = "[вложения] " + messageBody
        if (jsonMessage.chat_id) {
            dialogId = jsonMessage.chat_id
            chatsUids += "," + jsonMessage.user_id
            isChat = true
        } else {
            uids += "," + jsonMessage.user_id
        }
        formDialogsList(jsonMessage.out,
                        jsonMessage.title,
                        messageBody,
                        dialogId,
                        jsonMessage.read_state,
                        isChat)
    }
    if (uids.length === 0 && chatsUids.length === 0) {
        stopBusyIndicator()
    } else {
        uids = uids.substring(1)
        chatsUids = chatsUids.substring(1)
        UsersAPI.getUsersAvatarAndOnlineStatus(uids)
    }
}

function callback_getHistory(jsonObject) {
    var items = jsonObject.response.items
    for (var index in items) {
        formMessageList(parseMessage(items[index]))
    }
    stopLoadingMessagesIndicator()
    scrollMessagesToBottom()
}

function callback_sendMessage(jsonObject, isNew) {
    if (!isNew) api_getHistory(isChat, dialogId, messagesOffset)
}

function callback_createChat(jsonObject) {
    api_sendMessage(true, jsonObject.response, message, true)
}

function callback_searchDialogs(jsonObject) {
    for (var index in jsonObject.response) {
        var name = jsonObject.response[index].first_name
        name += " " + jsonObject.response[index].last_name
        updateSearchContactsList(jsonObject.response[index].id,
                                 name,
                                 jsonObject.response[index].photo_100,
                                 jsonObject.response[index].online)
    }
}

function callback_getChatUsers(jsonObject) {
    var users = []
    for (var index in jsonObject.response) {
        var name = jsonObject.response[index].first_name
        name += " " + jsonObject.response[index].last_name
        users[users.length] = {
            id:     jsonObject.response[index].id,
            name:   name,
            photo:  jsonObject.response[index].photo_100,
            online: jsonObject.response[index].online,
            status: jsonObject.response[index].status
        }
    }
    saveUsers(users)
}


// -------------- Other functions --------------


/**
 * The function for parsing the json object of a message.
 *
 * [In]  + jsonObject - the json object of the message.
 *
 * [Out] + The array of message data, which contains message and date.
 *         Also it can contain informaion about attachments, forwarded messages and location.
 */
function parseMessage(jsonObject) {
    var messageData = []

    var date = new Date()
    date.setTime(parseInt(jsonObject.date) * 1000)

    messageData[0] = jsonObject.id
    messageData[1] = jsonObject.from_id
    messageData[2] = jsonObject.read_state
    messageData[3] = jsonObject.out
    messageData[4] = jsonObject.body.replace(/(https?:\/\/[^\s<]+)/g, "<a href=\"$1\">$1</a>")
    console.log(jsonObject.body)
    console.log(messageData[3])
    messageData[5] = ("0" + date.getHours()).slice(-2) + ":" +
                     ("0" + date.getMinutes()).slice(-2) + ", " +
                     ("0" + date.getDate()).slice(-2) + "." +
                     ("0" + (date.getMonth() + 1)).slice(-2) + "." +
                     ("0" + date.getFullYear()).slice(-2)

    if (jsonObject.attachments) {
        for (var index in jsonObject.attachments) {
            messageData[messageData.length] = jsonObject.attachments[index]
        }
    }


    if (jsonObject.fwd_messages) {
        for (var index in jsonObject.fwd_messages) {
            messageData[messageData.length] = jsonObject.fwd_messages[index]
        }
    }

    if (jsonObject.geo) {
        messageData[messageData.length] = jsonObject.geo
    }

    return messageData
}
