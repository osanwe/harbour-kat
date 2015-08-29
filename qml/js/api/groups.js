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

.import "request.js" as RequestAPI


// -------------- API functions --------------

function api_getModeredGroups() {
    RequestAPI.sendRequest("groups.get",
                           { extended: 1,
                             filter: "moder",
                             count: 1000 },
                           callback_search)
}

function api_search(query) {
    RequestAPI.sendRequest("groups.search",
                           { q: query },
                           callback_search)
}


// -------------- Callbacks --------------

function callback_get(jsonObject) {
    var items = jsonObject.response.items
    for (var index in items) {
        addGroupToList(items[index].id, items[index].name)
    }
}

function callback_search(jsonObject) {
    var items = jsonObject.response.items
    for (var index in items) {
        if (items[index].is_admin === 1) {
            addGroupToList(items[index].id, items[index].name)
        }
    }
}


// -------------- Other functions --------------
