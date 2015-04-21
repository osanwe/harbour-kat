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

function getAudio(oid, aid) {
    var url = "https://api.vk.com/method/"
    url += "audio.get?"
    url += "owner_id=" + oid
    url += "&audio_ids=" + aid
    url += "&access_token=" + StorageJS.readSettingsValue("access_token")
    console.log(url)

    var doc = new XMLHttpRequest()
    doc.onreadystatechange = function() {
        if (doc.readyState === XMLHttpRequest.DONE) {
            console.log(doc.responseText)
            var jsonObject = JSON.parse(doc.responseText)
            playAudio(jsonObject.response[1].url, jsonObject.response[1].duration)
        }
    }
    doc.open("GET", url, true)
    doc.send()
}
