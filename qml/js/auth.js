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
