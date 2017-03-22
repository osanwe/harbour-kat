#ifndef FILESAVER_H
#define FILESAVER_H

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QStandardPaths>

#include <QDebug>

class FileSaver : public QObject
{
    Q_OBJECT

public:
    explicit FileSaver(QObject *parent = 0);
    ~FileSaver();

    Q_INVOKABLE void save(QString url);

public slots:
    void finished(QNetworkReply *reply);

private:
    QNetworkAccessManager *_manager;
};

#endif // FILESAVER_H
