var accessToken = ""
var userId

function checkUrl(url) {
    var startIndex = url.toString().indexOf("access_token=")
    if (startIndex !== -1) {
        startIndex += 13
        var endIndex = url.toString().indexOf("&", startIndex)
        accessToken = url.toString().substring(startIndex, endIndex)
        userId = url.toString().substring(url.toString().indexOf("user_id=")+8)
        return 0
    } else {
        return 1
    }
}
