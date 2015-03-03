function getUsersAvatar(uid) {
    var url = "https://api.vk.com/method/"
    url += "users.get?"
    url += "user_ids=" + uid
    url += "&fields=photo_100"
    url += "&access_token=" + StorageJS.readSettingsValue("access_token")
    console.log(url)

    var doc = new XMLHttpRequest()
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            var jsonObject = JSON.parse(doc.responseText)
            console.log(doc.responseText)
            for (var index in jsonObject.response) {
                updateDialogsList(index, jsonObject.response[index].photo_100)
            }
        }
    }
    doc.open("GET", url, true)
    doc.send()
}
