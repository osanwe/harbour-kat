.import QtQuick.LocalStorage 2.0 as LS

function getDatabase() {
    return LS.LocalStorage.openDatabaseSync("vkFish", "1", "Properties and data", 100000)
}

function initDatabase() {
    console.log("initDatabase()")
    var db = getDatabase()
    db.transaction( function(tx) {
        console.log("... create tables")
//        tx.executeSql("DROP TABLE settings")
        tx.executeSql("CREATE TABLE IF NOT EXISTS settings (key TEXT UNIQUE, value TEXT)")
    })
}

function storeSettingsValue(key, value) {
    console.log("storeSettingsData()")
    var db = getDatabase()
    db.transaction( function(tx) {
        console.log("... update it")
        tx.executeSql("INSERT OR REPLACE INTO settings VALUES (\"" + key + "\", \"" + value + "\")")
    })
}

function readSettingsValue(key) {
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
    return value
}
