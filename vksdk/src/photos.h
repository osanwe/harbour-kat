#ifndef PHOTOS_H
#define PHOTOS_H

#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkReply>
#include <QObject>
#include <QString>
#include <QUrlQuery>

#include "apirequest.h"

class Photos : public QObject
{
    Q_OBJECT
public:
    explicit Photos(QObject *parent = 0);
    ~Photos();

    void setAccessToken(const QString &accessToken);

signals:
    void imageUploaded(QString imageName);

public slots:
    void attachImage(QString image, QString mode, int groupId);

private slots:
    void gotServer(QJsonValue value, ApiRequest::TaskType type);
    void savedImage(QJsonValue value, ApiRequest::TaskType type);
    void uploadedImage(QNetworkReply *reply);

private:
    QString pathToImage;
    QString mMode;
    int mGroupId;
//    ApiRequest *request;

    QString _accessToken;

    void uploadFileToServer(QString url);
    void api_getMessagesUploadServer();
    void api_getWallUploadServer();
};

#endif // PHOTOS_H
