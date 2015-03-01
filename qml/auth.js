var accessToken = ""

function checkUrl(url) {
    var startIndex = url.toString().indexOf("access_token=")
    if (startIndex !== -1) {
        startIndex += 13
        var endIndex = url.toString().indexOf("&", startIndex)
        accessToken = url.toString().substring(startIndex, endIndex)
        return 0
    } else {
        return 1
    }
}
