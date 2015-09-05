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

Photos::Photos(QObject *parent) :
    QObject(parent)
{
//    request = new ApiRequest();
}

Photos::~Photos() {
//    delete request;
//    request = 0;
}

void Photos::attachImage(QString image, QString mode) {
    pathToImage = image.replace("file://", "");
    mMode = mode;
    if (mode == "MESSAGE") api_getMessagesUploadServer();
    else if (mode == "WALL") api_getWallUploadServer();
}

void Photos::gotServer(QString jsonData) {
    QJsonDocument document = QJsonDocument::fromJson(jsonData.toUtf8());
    QJsonObject object = document.object();

    qDebug() << object.value("response").toObject().value("upload_url").toString();
    uploadFileToServer(object.value("response").toObject().value("upload_url").toString());
}

void Photos::savedImage(QString jsonData) {
    qDebug() << jsonData;
    QJsonObject object = QJsonDocument::fromJson(jsonData.toUtf8()).object().value("response").toArray().at(0).toObject();
    emit imageUploaded(QString("photo%1_%2").arg(QString::number(object.value("owner_id").toInt()),
                                                 QString::number(object.value("id").toInt())));
}

void Photos::uploadedImage(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QString jsonData = reply->readAll();
        qDebug() << jsonData;
        QHash<QString, QString> args;
        QJsonObject object = QJsonDocument::fromJson(jsonData.toUtf8()).object();
        args["server"] = QString::number(object.value("server").toInt());
        args["photo"] = object.value("photo").toString();
        args["hash"] = object.value("hash").toString();

        ApiRequest *request = new ApiRequest(this);
        connect(request, SIGNAL(finished(QString)), this, SLOT(savedImage(QString)));
        if (mMode == "MESSAGE") request->startRequest("photos.saveMessagesPhoto", args);
        else if (mMode == "WALL") request->startRequest("photos.saveWallPhoto", args);
    } else qDebug() << "Failture:" << reply->errorString();
}

void Photos::uploadFileToServer(QString url) {
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"photo\"; filename=\"" + pathToImage.split("/").last() + "\""));
    QFile *file = new QFile(pathToImage);
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart);

    multiPart->append(imagePart);

    QNetworkRequest req((QUrl(url)));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    multiPart->setParent(manager);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(uploadedImage(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    manager->post(req, multiPart);
}

void Photos::api_getMessagesUploadServer() {
    ApiRequest *request = new ApiRequest(this);
    connect(request, SIGNAL(finished(QString)), this, SLOT(gotServer(QString)));
    request->startRequest("photos.getMessagesUploadServer", QHash<QString, QString>());
}

void Photos::api_getWallUploadServer() {
    ApiRequest *request = new ApiRequest(this);
    connect(request, SIGNAL(finished(QString)), this, SLOT(gotServer(QString)));
    request->startRequest("photos.getWallUploadServer", QHash<QString, QString>());
}
