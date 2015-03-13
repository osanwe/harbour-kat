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
                    if (jsonObject.response[index].attachment) messageBody = "[вложение] " + messageBody
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
            uids = uids.substring(1)
            chatsUids = chatsUids.substring(1)
            UsersAPI.getUsersAvatar(uids)
        }
    }
    doc.open("GET", url, true)
    doc.send()
}

function sendMessage(isChat, dialogId, message) {
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
            sendMessage(true, jsonObject.response, message)
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
                    var msg = ""
                    var msgParts = jsonObject.response[index].body.split(" ")
                    var idx = 0
                    while (idx < msgParts.length) {
                        console.log(msgParts[idx])
                        if (msgParts[idx].search("http") === 0) {
                            msg = msg + " <a href=\"" + msgParts[idx] + "\">" + msgParts[idx] + "</a>"
                        } else {
                            msg = msg + " " + msgParts[idx]
                        }
                        idx = idx + 1
                    }

                    if (jsonObject.response[index].attachment) msg = "[вложение] " + msg
                    formMessagesList(jsonObject.response[index].out, jsonObject.response[index].read_state, msg)
                }
            }
            if (index > 1) scrollMessagesToBottom()
        }
    }
    doc.open("GET", url, true)
    doc.send()
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
