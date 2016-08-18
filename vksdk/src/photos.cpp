#include "photos.h"

#include <QByteArray>
#include <QFile>
#include <QIODevice>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>

#include <QHttpMultiPart>
#include <QHttpPart>

#include <QJsonArray>

Photos::Photos(QObject *parent) : QObject(parent)
{}

Photos::~Photos()
{}

void Photos::attachImage(QString image, QString mode, int groupId) {
    pathToImage = image.replace("file://", "");
//    pathToImage = image;
    mMode = mode;
    mGroupId = groupId;
    if (mode == "MESSAGE") api_getMessagesUploadServer();
    else if (mode == "WALL") api_getWallUploadServer();
}

void Photos::gotServer(QJsonValue value, ApiRequest::TaskType type) {
    QJsonObject object = value.toObject();
    uploadFileToServer(object.value("upload_url").toString());
}

void Photos::savedImage(QJsonValue value, ApiRequest::TaskType type) {
    qDebug() << value;
    QJsonObject object = value.toArray().at(0).toObject();
    emit imageUploaded(QString("photo%1_%2").arg(QString::number(object.value("owner_id").toInt()),
                                                 QString::number(object.value("id").toInt())));
}

void Photos::uploadedImage(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QString jsonData = reply->readAll();
        qDebug() << jsonData;
        QJsonObject object = QJsonDocument::fromJson(jsonData.toUtf8()).object();

        QUrlQuery *query = new QUrlQuery();
        if (mGroupId != 0) query->addQueryItem("group_id", QString::number(mGroupId));
        query->addQueryItem("server", QString::number(object.value("server").toInt()));
        query->addQueryItem("photo", object.value("photo").toString());
        query->addQueryItem("hash", object.value("hash").toString());

        ApiRequest *request = new ApiRequest(this);
        connect(request, SIGNAL(gotResponse(QJsonValue,ApiRequest::TaskType)),
                this, SLOT(savedImage(QJsonValue,ApiRequest::TaskType)));
        request->setAccessToken(_accessToken);

        if (mMode == "MESSAGE") request->makeApiGetRequest("photos.saveMessagesPhoto", query,
                                                      ApiRequest::PHOTOS_SAVE_MESSAGES_PHOTO);
        else if (mMode == "WALL") request->makeApiGetRequest("photos.saveWallPhoto", query,
                                                        ApiRequest::PHOTOS_SAVE_WALL_PHOTO);
    } else qDebug() << "Failture:" << reply->errorString();
}

void Photos::setAccessToken(const QString &accessToken) {
    _accessToken = accessToken;
}

void Photos::uploadFileToServer(QString url) {
    QFile *file = new QFile(pathToImage);
    file->open(QIODevice::ReadOnly);
    QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/*"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"photo\"; filename=\"" + pathToImage.split("/").last() + "\""));
    imagePart.setHeader(QNetworkRequest::ContentLengthHeader, file->size());
    imagePart.setBody(file->readAll());
    multipart->append(imagePart);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(uploadedImage(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    QNetworkRequest req((QUrl(url)));
    manager->post(req, multipart);
    file->close();

//    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

//    QHttpPart imagePart;
//    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
//    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"photo\"; filename=\"" + pathToImage.split("/").last() + "\""));
//    QFile *file = new QFile(pathToImage);
//    file->open(QIODevice::ReadOnly);
//    imagePart.setBodyDevice(file);
//    file->setParent(multiPart);

//    multiPart->append(imagePart);

//    QNetworkRequest req((QUrl(url)));
//    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
//    multiPart->setParent(manager);

//    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(uploadedImage(QNetworkReply*)));
//    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
//    manager->post(req, multiPart);
}

void Photos::api_getMessagesUploadServer() {
    ApiRequest *request = new ApiRequest(this);
    connect(request, SIGNAL(gotResponse(QJsonValue,ApiRequest::TaskType)),
            this, SLOT(gotServer(QJsonValue,ApiRequest::TaskType)));
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("photos.getMessagesUploadServer", new QUrlQuery(), ApiRequest::PHOTOS_GET_MESSAGES_UPLOAD_SERVER);
}

void Photos::api_getWallUploadServer() {
    QUrlQuery *query = new QUrlQuery();
    if (mGroupId != 0) query->addQueryItem("group_id", QString::number(mGroupId));
    ApiRequest *request = new ApiRequest(this);
    connect(request, SIGNAL(gotResponse(QJsonValue,ApiRequest::TaskType)),
            this, SLOT(gotServer(QJsonValue,ApiRequest::TaskType)));
    request->setAccessToken(_accessToken);
    request->makeApiGetRequest("photos.getWallUploadServer", query, ApiRequest::PHOTOS_GET_MESSAGES_UPLOAD_SERVER);
}
