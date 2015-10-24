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

.pragma library
.import "storage.js" as StorageJS

var Action = {
    ADD: 0,
    SET: 1,
    DEL: 2
}

var LongPollMode = {
    ATTACH: 2, // получать прикрепления
    VIDEO: 8, // возвращать расширенный набор событий (видеозвонки)
    PTS: 32, // возвращать pts
    EXTRA: 64 // возвращать дополнительные данные
}

var MsgFlag = {
    UNREAD: 1, // сообщение не прочитано
    OUTBOX: 2,	// исходящее сообщение
    REPLIED: 4,	// на сообщение был создан ответ
    IMPORTANT: 8, // помеченное сообщение
    CHAT: 16, // сообщение отправлено через чат
    FRIENDS: 32, // сообщение отправлено другом
    SPAM: 64, // сообщение помечено как "Спам"
    DELETED: 128, // сообщение удалено (в корзине)
    FIXED: 256, // сообщение проверено пользователем на спам
    MEDIA: 512 // сообщение содержит медиаконтент
}

var UpdateInterval = {
    items: [{
        name: "15 min",
        value: 900
    }, {
        name: "5 min",
        value: 300
    }, {
        name: "1 min",
        value: 60
    }, {
        name: "25 sec",
        value: 25
    }],
    index: 0,

    getValue: function() {
        this.index = parseInt(StorageJS.readSettingsValue("update_interval", 3), 10)

        if (this.items.length > this.index) return this.items[this.index].value

        return -1
    }
}

var LongPollWorker = {
    lastActive: 0,

//    addValues: function(values) {
//        for (var key in values) this.addValue(key, values[key])
//    },

//    delValue: function(key) {
//        if (key in this.items) return delete this.items[key]
//        return false
//    },

//    delValues: function(keys) {
//        for (var i in keys) this.delValue(keys[i])
//    },

//    getValue: function(key) {
//        if (key in this.items) return this.items[key]
//        return function() {}
//    },

    setActive: function() {
        this.lastActive = Date.now()
    },

    isActive: function() {
        var diff = Date.now() - this.lastActive
        return diff <= 25000
    }
}


var MessageUpdateMode = {
    isManual: function() {
        return StorageJS.readSettingsValue("update_manual", 'false') === 'true'
    }
}
