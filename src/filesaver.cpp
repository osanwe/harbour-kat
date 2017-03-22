#include "filesaver.h"

FileSaver::FileSaver(QObject *parent) : QObject(parent) {
    _manager = new QNetworkAccessManager(this);
    connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
}

FileSaver::~FileSaver() {
    delete _manager;
    _manager = NULL;
}

void FileSaver::save(QString url) {
    _manager->get(QNetworkRequest(QUrl(url)));
}

void FileSaver::finished(QNetworkReply *reply) {
    QFile *file = new QFile(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/" + reply->url().fileName());
    if (file->open(QIODevice::WriteOnly)) {
        file->write(reply->readAll());
        file->close();
    }
    reply->deleteLater();
}
