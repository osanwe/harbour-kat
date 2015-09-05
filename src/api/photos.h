#ifndef PHOTOS_H
#define PHOTOS_H

#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
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
    void imageUploaded(QString imageName);

public slots:
    void attachImage(QString image);

private slots:
    void gotServer(QString jsonData);
    void savedImage(QString jsonData);
    void uploadedImage(QNetworkReply *reply);

private:
    QString pathToImage;
//    ApiRequest *request;

    void uploadFileToServer(QString url);
    void api_getMessagesUploadServer();
};

#endif // PHOTOS_H
