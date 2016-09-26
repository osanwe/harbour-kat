/*
  Copyright (C) 2016 Petr Vytovtov
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

#ifndef PHOTOS_H
#define PHOTOS_H

#include <QDebug>

//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QJsonValue>
//#include <QNetworkReply>
#include <QObject>
//#include <QString>
//#include <QUrlQuery>

//#include <QByteArray>
#include <QFile>
#include <QTextCodec>
//#include <QIODevice>
//#include <QNetworkAccessManager>
//#include <QNetworkRequest>
//#include <QUrl>

#include <QHttpMultiPart>
#include <QHttpPart>

//#include <QJsonArray>

#include "apirequest.h"

class Photos : public QObject
{
    Q_OBJECT
public:
    explicit Photos(QObject *parent = 0);
    ~Photos();

    void setApi(ApiRequest *api);

    void getMessagesUploadServer();
    void uploadPhotoToServer(QString server, QString album, QString user, QString path);
    void saveMessagesPhoto(QString photo, QString server, QString hash);

//    void setAccessToken(const QString &accessToken);

//signals:
//    void imageUploaded(QString imageName);

//public slots:
//    void attachImage(QString image, QString mode, int groupId);

//private slots:
//    void gotServer(QJsonValue value, ApiRequest::TaskType type);
//    void savedImage(QJsonValue value, ApiRequest::TaskType type);
//    void uploadedImage(QNetworkReply *reply);

private:
    ApiRequest *_api;
    //    QString pathToImage;
//    QString mMode;
//    int mGroupId;
////    ApiRequest *request;

//    QString _accessToken;

//    void uploadFileToServer(QString url);
//    void api_getMessagesUploadServer();
//    void api_getWallUploadServer();
};

#endif // PHOTOS_H
