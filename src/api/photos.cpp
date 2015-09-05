#include "photos.h"

#include <QByteArray>
#include <QFile>
#include <QIODevice>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>

#include <QHttpMultiPart>
#include <QHttpPart>

Photos::Photos(QObject *parent) :
    QObject(parent)
{
    request = new ApiRequest();
}

Photos::~Photos() {
    delete request;
    request = 0;
}

void Photos::attachImage(QString image) {
    pathToImage = image.replace("file://", "");
    api_getMessagesUploadServer();
}

void Photos::gotServer(QString jsonData) {
    disconnect(request, SIGNAL(finished(QString)), this, SLOT(gotServer(QString)));

    QJsonDocument document = QJsonDocument::fromJson(jsonData.toUtf8());
    QJsonObject object = document.object();

    qDebug() << object.value("response").toObject().value("upload_url").toString();
    uploadFileToServer(object.value("response").toObject().value("upload_url").toString());
}

void Photos::uploadedImage(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) qDebug() << reply->readAll();
    else qDebug() << "Failture:" << reply->errorString();
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
    connect(request, SIGNAL(finished(QString)), this, SLOT(gotServer(QString)));
    request->startRequest("photos.getMessagesUploadServer", QHash<QString, QString>());
}
