#include "photos.h"

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
}

void Photos::api_getMessagesUploadServer() {
    connect(request, SIGNAL(finished(QString)), this, SLOT(gotServer(QString)));
    request->startRequest("photos.getMessagesUploadServer", QHash<QString, QString>());
}
