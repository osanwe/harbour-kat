/*
  Copyright (C) 2015 Albert Shteiner
  Contact: Albert Shteiner <ckazzku@gmail.com>
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

.import "storage.js" as StorageJS

var UpdateInterval = {
    items: [{
        name: "15 min",
        value: 900000
    }, {
        name: "5 min",
        value: 300000
    }, {
        name: "1 min",
        value: 60000
    }, {
        name: "30 sec",
        value: 30000
    }],
    index: 0,

    getValue: function() {
        this.index = parseInt(StorageJS.readSettingsValue("update_interval"), 10)

        if (this.items.length > this.index)
            return this.items[this.index].value

        return -1
    }
}
