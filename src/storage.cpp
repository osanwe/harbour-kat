#include "storage.h"

Storage::Storage(QObject *parent) :
    QObject(parent)
{
    mDb = QSqlDatabase::addDatabase("QSQLITE");
    mDb.setDatabaseName(getPathToDatabase());
}

QString Storage::getAccessToken() {
    QString accessToken;
    if (!mDb.open()) return accessToken;

    QSqlQuery query("SELECT value FROM settings WHERE key=\"access_token\"");
    if (query.next()) accessToken = query.value(0).toString();

    mDb.close();
    return accessToken;
}

QString Storage::getPathToDatabase() {
    QString pathToDatabase;

    QStringList cacheLocation = QStandardPaths::standardLocations(QStandardPaths::DataLocation);
    if (cacheLocation.isEmpty()) pathToDatabase = getenv("$XDG_DATA_HOME/harbour-kat/");
    else pathToDatabase = QString("%1/").arg(cacheLocation.first());
    pathToDatabase = pathToDatabase.append("QML/OfflineStorage/Databases/");

    QDir dir(pathToDatabase);
    QStringList files = dir.entryList(QStringList() << "*.sqlite");
    if (!files.isEmpty()) pathToDatabase = pathToDatabase.append(files.first());

    qDebug() << "Path to database:" << pathToDatabase;
    return pathToDatabase;
}

bool Storage::clearCache() {
    qDebug() << "Storage::clearCache()";
    if (!mDb.open()) false;

    QSqlQuery query("DELETE FROM messages");
    bool result = query.numRowsAffected() != -1;
    result = result && query.exec("DELETE FROM dialogs");
    result = result && query.exec("DELETE FROM users");
    result = result && query.exec("DELETE FROM user_info");

    mDb.close();
    return result;
}
