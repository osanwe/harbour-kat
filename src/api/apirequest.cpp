#include "apirequest.h"

#include <QDebug>

ApiRequest::ApiRequest(QObject *parent)
    : QObject(parent)
{
    BASE_URL = "https://api.vk.com/method/";
    API_VERSION = "?v=5.35";
}

void ApiRequest::startRequest(QString method, QHash<QString, QString> args) {
    QString url = "";
    QHashIterator<QString, QString> iterator(args);
    url = url.append(BASE_URL).append(method).append(API_VERSION);
    url = url.append("&access_token=").append(Storage().getAccessToken());
    while (iterator.hasNext()) {
        iterator.next();
        url = url.append("&").append(iterator.key()).append("=").append(iterator.value());
    }

    qDebug() << url;

    QNetworkAccessManager *mgr = new QNetworkAccessManager(this);
    connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpFinished(QNetworkReply*)));
    connect(mgr, SIGNAL(finished(QNetworkReply*)), mgr, SLOT(deleteLater()));

    mgr->get(QNetworkRequest(QUrl(url)));
}

void ApiRequest::httpFinished(QNetworkReply *rep) {
    if (rep->error() == QNetworkReply::NoError) qDebug() << "Success:" << rep->readAll();
    else qDebug() << "Failture:" << rep->errorString();
}
