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
.import "./users.js" as UsersAPI

function getDialogs(offset) {
    var url = "https://api.vk.com/method/"
    url += "messages.getDialogs?"
    url += "offset=" + offset
    url += "&access_token=" + StorageJS.readSettingsValue("access_token")
    console.log(url)

    var doc = new XMLHttpRequest()
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            var jsonObject = JSON.parse(doc.responseText)
            console.log(doc.responseText)
            var uids = ""
            var chatsUids = ""
            for (var index in jsonObject.response) {
                if (index > 0) {
                    var dialogId = jsonObject.response[index].uid
                    var messageBody = jsonObject.response[index].body
                    var isChat = false
                    if (jsonObject.response[index].fwd_messages)
                        messageBody = "[сообщения] " + messageBody
                    if (jsonObject.response[index].attachments)
                        messageBody = "[вложения] " + messageBody
                    if (jsonObject.response[index].chat_id) {
                        dialogId = jsonObject.response[index].chat_id
                        chatsUids += "," + jsonObject.response[index].uid
                        isChat = true
                    } else {
                        uids += "," + jsonObject.response[index].uid
                    }
                    formDialogsList(jsonObject.response[index].out,
                                    jsonObject.response[index].title,
                                    messageBody,
                                    dialogId,
                                    jsonObject.response[index].read_state,
                                    isChat)
                }
            }
            if (uids.length === 0 && chatsUids.length === 0) {
                stopBusyIndicator()
            } else {
                uids = uids.substring(1)
                chatsUids = chatsUids.substring(1)
                UsersAPI.getUsersAvatarAndOnlineStatus(uids)
            }
        }
    }
    doc.open("GET", url, true)
    doc.send()
}

function sendMessage(isChat, dialogId, message, isNew) {
    var url = "https://api.vk.com/method/"
    url += "messages.send?"
    if (isChat) {
        url += "chat_id=" + dialogId
    } else {
        url += "user_id=" + dialogId
    }
    url += "&message=" + message
    url += "&access_token=" + StorageJS.readSettingsValue("access_token")
    console.log(url)

    var doc = new XMLHttpRequest()
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            if (!isNew) getHistory(isChat, dialogId, messagesOffset)
        }
    }
    doc.open("GET", url, true)
    doc.send()
}

function sendGroupMessage(ids, message) {
    var url = "https://api.vk.com/method/"
    url += "messages.createChat?"
    url += "user_ids=" + ids
    url += "&message=" + message
    url += "&access_token=" + StorageJS.readSettingsValue("access_token")
    console.log(url)

    var doc = new XMLHttpRequest()
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            var jsonObject = JSON.parse(doc.responseText)
            console.log(doc.responseText)
            sendMessage(true, jsonObject.response, message, true)
        }
    }
    doc.open("GET", url, true)
    doc.send()
}

function getHistory(isChat, dialogId, offset) {
    var url = "https://api.vk.com/method/"
    url += "messages.getHistory?"
    if (isChat) {
        url += "chat_id=" + dialogId
    } else {
        url += "user_id=" + dialogId
    }
    url += "&offset=" + offset
    url += "&count=50"
    url += "&access_token=" + StorageJS.readSettingsValue("access_token")
    console.log(url)

    var doc = new XMLHttpRequest()
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            var jsonObject = JSON.parse(doc.responseText)
            console.log(doc.responseText)
            for (var index in jsonObject.response) {
                if (index > 0) {
                    parseMessage(jsonObject.response[index])
// --------------
                    var msg = ""
                    var msgParts = jsonObject.response[index].body.split(" ")
                    var idx = 0
                    while (idx < msgParts.length) {
                        if (msgParts[idx].search("http") === 0) {
                            msg = msg + " <a href=\"" + msgParts[idx] + "\">" + msgParts[idx] + "</a>"
                        } else {
                            msg = msg + " " + msgParts[idx]
                        }
                        idx = idx + 1
                    }
// --------------
                    var attachments = ""
                    if (jsonObject.response[index].fwd_messages) {
                        attachments = attachments + "<br /><a href=\"#\">Пересланные сообщения</a>"
                    }
                    if (jsonObject.response[index].attachments) {
                        var photosCounter = 0
                        var videosCounter = 0
                        var audiosCounter = 0
                        var docsCounter = 0
                        var wallsCounter = 0
                        for (var itemIdx in jsonObject.response[index].attachments)
                            switch (jsonObject.response[index].attachments[itemIdx].type) {
                                case "photo": photosCounter += 1; break
                                case "video": videosCounter += 1; break
                                case "audio": audiosCounter += 1; break
                                case "doc": docsCounter += 1; break
                                case "wall": wallsCounter += 1; break
                            }
                        if (photosCounter > 0) attachments += "<br /><a href=\"#\">Фотография (" + photosCounter + ")</a>"
                        if (videosCounter > 0) attachments += "<br /><a href=\"#\">Видео (" + videosCounter + ")</a>"
                        if (audiosCounter > 0) attachments += "<br /><a href=\"#\">Аудио (" + audiosCounter + ")</a>"
                        if (docsCounter > 0) attachments += "<br /><a href=\"#\">Документ (" + docsCounter + ")</a>"
                        if (wallsCounter > 0) attachments += "<br /><a href=\"#\">Запись на стене (" + wallsCounter + ")</a>"
                    }
                    if (jsonObject.response[index].geo) {
                        attachments += "<br /><a href=\"#\">Карта</a>"
                    }

                    attachments = attachments.substring(6)

                    var date = new Date()
                    date.setTime(parseInt(jsonObject.response[index].date) * 1000)

                    formMessagesList(jsonObject.response[index].mid,
                                     jsonObject.response[index].out,
                                     jsonObject.response[index].read_state,
                                     msg,
                                     date.toLocaleString(),
                                     attachments)
                }
            }
            stopLoadingMessagesIndicator()
            if (index > 1) scrollMessagesToBottom()
        }
    }
    doc.open("GET", url, true)
    doc.send()
}

function parseMessage(jsonObject) {
    var msgData = []

    msgData[0] = jsonObject.body.replace(/(https?:\/\/[^\s]+)/g, "<a href=\"$1\">$1</a>")


    if (jsonObject.fwd_messages) {
        msgData[msgData.length] = 'Пересланные сообщения (' + jsonObject.fwd_messages.length + ')'
        msgData[msgData.length] = jsonObject.fwd_messages
    }

    console.log(msgData)
}

function getUnreadMessagesCount() {
    var url = "https://api.vk.com/method/"
    url += "messages.getDialogs?v=5.14"
    url += "&unread=1"
    url += "&access_token=" + StorageJS.readSettingsValue("access_token")
    console.log(url)

    var doc = new XMLHttpRequest()
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            var jsonObject = JSON.parse(doc.responseText)
            console.log(doc.responseText)
            if (jsonObject.response.count) {
                updateCoverCounters(jsonObject.response.count)
            } else {
                updateCoverCounters(0)
            }
        }
    }
    doc.open("GET", url, true)
    doc.send()
}

function searchDialogs(substring) {
    var url = "https://api.vk.com/method/"
    url += "messages.searchDialogs?"
    url += "q=" + substring
    url += "&fields=photo_100,online"
    url += "&access_token=" + StorageJS.readSettingsValue("access_token")
    console.log(url)

    var doc = new XMLHttpRequest()
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            var jsonObject = JSON.parse(doc.responseText)
            console.log(doc.responseText)
            for (var index in jsonObject.response) {
                var name = jsonObject.response[index].first_name
                name += " " + jsonObject.response[index].last_name
                updateSearchContactsList(jsonObject.response[index].uid,
                                         name,
                                         jsonObject.response[index].photo_100,
                                         jsonObject.response[index].online)
            }
        }
    }
    doc.open("GET", url, true)
    doc.send()
}

function markDialogAsRead(isChat, uid) {
    var url = "https://api.vk.com/method/"
    url += "messages.markAsRead?"
    url += "peer_id=" + uid
    url += "&access_token=" + StorageJS.readSettingsValue("access_token")
    console.log(url)

    var doc = new XMLHttpRequest()
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            getHistory(isChat, uid, 0)
        }
    }
    doc.open("GET", url, true)
    doc.send()
}

function getChatUsers(dialogId) {
    var url = "https://api.vk.com/method/"
    url += "messages.getChatUsers?"
    url += "chat_id=" + dialogId
    url += "&fields=online,photo_100,status"
    url += "&access_token=" + StorageJS.readSettingsValue("access_token")
    console.log(url)

    var doc = new XMLHttpRequest()
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            var jsonObject = JSON.parse(doc.responseText)
            console.log(doc.responseText)
            for (var index in jsonObject.response) {
                var name = jsonObject.response[index].first_name
                name += " " + jsonObject.response[index].last_name
                appendUser(jsonObject.response[index].uid,
                           name,
                           jsonObject.response[index].photo_100,
                           jsonObject.response[index].online,
                           jsonObject.response[index].status)
            }
        }
    }
    doc.open("GET", url, true)
    doc.send()
}
