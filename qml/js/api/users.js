function getUsersAvatar(uid) {
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
                var fullname = jsonObject.response[index].first_name + " " + jsonObject.response[index].last_name
                updateDialogsList(index, jsonObject.response[index].photo_100, fullname, jsonObject.response[index].online)
            }
        }
    }
    doc.open("GET", url, true)
    doc.send()
}
