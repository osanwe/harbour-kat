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

#include "requestbase.h"

class Photos : public RequestBase
{
    Q_OBJECT
public:
    explicit Photos(QObject *parent = 0);

    void getMessagesUploadServer();
    void uploadPhotoToServer(const QString &server, const QString &album, const QString &user, const QString &path);
    void saveMessagesPhoto(const QString &photo, const QString &server, const QString &hash);

    Q_INVOKABLE void get(QString ownerId, QString albumId, int offset = 0);
    Q_INVOKABLE void getAlbums(QString ownerId);
    Q_INVOKABLE void getAll(QString ownerId, int offset = 0);

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
