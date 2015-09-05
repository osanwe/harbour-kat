#ifndef PHOTOS_H
#define PHOTOS_H

#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QString>

#include "apirequest.h"

class Photos : public QObject
{
    Q_OBJECT
public:
    explicit Photos(QObject *parent = 0);
    ~Photos();

signals:

public slots:
    void attachImage(QString image);

private slots:
    void gotServer(QString jsonData);

private:
    QString pathToImage;
    ApiRequest *request;

    void api_getMessagesUploadServer();
};

#endif // PHOTOS_H
