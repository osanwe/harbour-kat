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

.import QtQuick.LocalStorage 2.0 as LS


var DATABASE_VERSION = "2"

function getDatabase() {
    return LS.LocalStorage.openDatabaseSync("harbour-kat-db", "", "Properties and data", 100000)
}

function initDatabase() {
    console.log("initDatabase()")
    var db = getDatabase()
    console.log("db.version = " + db.version)
    if (db.version === "") {
        db.changeVersion(db.version, DATABASE_VERSION, function(tx) {
            console.log("... create tables")
            tx.executeSql("CREATE TABLE IF NOT EXISTS settings (key TEXT UNIQUE, value TEXT)")
            tx.executeSql("CREATE TABLE IF NOT EXISTS user_info (key TEXT UNIQUE, value TEXT)")
        })
    } else if (db.version !== DATABASE_VERSION) {
        db.changeVersion(db.version, DATABASE_VERSION, function(tx) {
            console.log("... recreate tables")
            tx.executeSql("DELETE FROM settings")
        })
    }
}


// -------------- Functions for saving and reading settings parameters --------------

function storeSettingsValue(key, value) {
    console.log("storeSettingsData()")
    var db = getDatabase()
    if (!db) { return }
    db.transaction( function(tx) {
        console.log("... update it")
        tx.executeSql("INSERT OR REPLACE INTO settings VALUES (\"" + key + "\", \"" + value + "\")")
    })
}

function readSettingsValue(key, default_value) {
    console.log("readData()")
    var db = getDatabase()
    if (!db) { return }
    var value = ""
    db.transaction( function(tx) {
        console.log("... read object")
        var result = tx.executeSql("SELECT value FROM settings WHERE key=\"" + key + "\"")
        if (result.rows.length === 1) {
            value = result.rows[0].value
        }
    })
    console.log(value)
    if (value === "")
        value = default_value
    return value
}


// -------------- Functions for saving user data --------------

function saveUserName(first_name, last_name) {
    console.log("saveUserName()")
    var db = getDatabase()
    if (!db) { return }
    db.transaction( function(tx) {
        console.log("... saving ...")
        tx.executeSql("INSERT OR REPLACE INTO user_info VALUES (\"first_name\", \"" + first_name + "\")")
        tx.executeSql("INSERT OR REPLACE INTO user_info VALUES (\"last_name\", \"" + last_name + "\")")
    })
}

function saveUserAvatar(fileName) {
    console.log("saveUserAvatar()")
    var db = getDatabase()
    if (!db) { return }
    db.transaction( function(tx) {
        console.log("... saving ...")
        tx.executeSql("INSERT OR REPLACE INTO user_info VALUES (\"user_avatar\", \"" + fileName + "\")")
    })
}


// -------------- Functions for reading user data --------------

function readFullUserName() {
    console.log("readFullUserName()")
    var db = getDatabase()
    if (!db) { return }
    var value = ""
    db.transaction( function(tx) {
        console.log("... reading ...")
        var result = tx.executeSql(
                    "SELECT value FROM user_info WHERE key=\"first_name\" OR key=\"last_name\"")
        if (result.rows.length === 2) {
            value = result.rows[0].value + " " + result.rows[1].value
        }
    })
    console.log(value)
    return value
}

function readUserAvatar() {
    console.log("readUserAvatar()")
    var db = getDatabase()
    if (!db) { return }
    var value = ""
    db.transaction( function(tx) {
        console.log("... reading ...")
        var result = tx.executeSql("SELECT value FROM user_info WHERE key=\"user_avatar\"")
        if (result.rows.length === 1) {
            value = result.rows[0].value
        }
    })
    console.log(value)
    return value
}
