.import "../storage.js" as StorageJS

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
            for (var index in jsonObject.response) {
                if (index > 0) {
                    updateMessagesList(jsonObject.response[index].uid, jsonObject.response[index].title, jsonObject.response[index].body)
                }
            }
        }
    }
    doc.open("GET", url, true)
    doc.send()
}
