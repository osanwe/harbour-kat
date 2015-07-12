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

const MESSAGE_API_VERSION = "5.14";
const HISTORY_COUNT = 50;

// -------------- API functions --------------

function api_getUnreadMessagesCounter(isCover) {
    RequestAPI.sendRequest("messages.getDialogs", MESSAGE_API_VERSION, {
                               unread:1
                           }, isCover ?
                                  callback_getUnreadMessagesCounter_cover :
                                  callback_getUnreadMessagesCounter_mainMenu)
}

function api_getDialogsList(offset) {
    RequestAPI.sendRequest("messages.getDialogs", MESSAGE_API_VERSION, {
                               offset: offset
                           }, callback_getDialogsList)
}

function api_getHistory(isChat, dialogId, offset) {
    var data = {
        offset: offset,
        count: HISTORY_COUNT
    };
    data[isChat ? "chat_id" : "user_id"] = dialogId;
    RequestAPI.sendRequest("messages.getHistory", MESSAGE_API_VERSION, data, callback_getHistory)
}

function api_sendMessage(isChat, dialogId, message, isNew) {
    var data = {
        message: message
    };
    data[isChat ? "chat_id" : "user_id"] = dialogId;
    RequestAPI.sendRequest("messages.send", MESSAGE_API_VERSION, data, callback_sendMessage)
}

function api_createChat(ids, message) {
    RequestAPI.sendRequest("messages.createChat", MESSAGE_API_VERSION, {
                               user_ids: ids,
                               title: message
                           }, callback_createChat)
}

function api_searchDialogs(substring) {
    RequestAPI.sendRequest("messages.searchDialogs", MESSAGE_API_VERSION, {
                               q: substring,
                               fields:"photo_100,online"
                           }, callback_searchDialogs)
}

function api_markDialogAsRead(isChat, uid, mids) {
    RequestAPI.sendRequest("messages.markAsRead", MESSAGE_API_VERSION, {
                             message_ids: mids
                           })
}

function api_getChatUsers(dialogId) {
    RequestAPI.sendRequest("messages.markAsRead", MESSAGE_API_VERSION, {
                               chat_id: dialogId,
                               fields: "online,photo_100,status"
                           }, callback_getChatUsers)
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
    messageData[4] = messageData[4].replace(/\n/g, "<br>")
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
