#ifndef STORAGE_H
#define STORAGE_H

#include <QDebug>

#include <QDir>
#include <QObject>
#include <QStandardPaths>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class Storage : public QObject
{
    Q_OBJECT
public:
    explicit Storage(QObject *parent = 0);

    QString getAccessToken();

signals:

public slots:

private:
    QSqlDatabase mDb;

    QString getPathToDatabase();
};

#endif // STORAGE_H
