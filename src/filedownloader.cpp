/*
  Copyright (C) 2015 Petr Vytovtov
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

#include "filedownloader.h"

#include <QDebug>

FileDownloader::FileDownloader(QObject *parent)
    : QObject(parent)
{
    connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)), this, SLOT(fileDownloaded(QNetworkReply*)));
}

FileDownloader::~FileDownloader()
{
}

void FileDownloader::startDownload(QString url, int mode)
{
    m_Mode = mode;
    m_FileName = url.split("/").last();
    QNetworkRequest request(url);
    m_WebCtrl.get(request);
}

bool FileDownloader::clearCache() {
    qDebug() << "FileDownloader::clearCache()";
    bool result = true;

    QUrl path;
    QStringList location = QStandardPaths::standardLocations(QStandardPaths::CacheLocation);
    if (location.isEmpty()) path = getenv("$XDG_CACHE_HOME/harbour-kat/");
    else path = location.first();

    QDir dir(path.toString());
    QStringList files = dir.entryList();
    for (int i = 0; i < files.size(); ++i) {
        if (!files.at(i).endsWith(".jpg")) continue;
        result = result && QFile::remove(QString("%1/%2").arg(path.toString(), files.at(i)));
    }

    return result;
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply) {
    m_DownloadedData = pReply->readAll();

    switch (m_Mode) {
    case SAVING_TO_CACHE:
    {
        QUrl path;
        QStringList location = QStandardPaths::standardLocations(QStandardPaths::CacheLocation);
        if (location.isEmpty()) path = QString("%1/%2").arg(getenv("$XDG_CACHE_HOME/harbour-kat/"), m_FileName);
        else path = QString("%1/%2").arg(location.first(), m_FileName);

//        QString path("/home/nemo/.cache/harbour-kat/");
        QFile file(path.toString());
        file.open(QIODevice::WriteOnly);
        file.write(m_DownloadedData);
        file.close();
        break;
    }

    case SAVING_TO_DOWNLOADS:
    {
        QUrl path;
        QStringList location = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
        if (location.isEmpty()) path = QString("%1/%2").arg(getenv("$HOME/Downloads/"), m_FileName);
        else path = QString("%1/%2").arg(location.first(), m_FileName);

//        QString path("/home/nemo/Downloads/");
//        QFile file(path.append(m_FileName));
        QFile file(path.toString());
        file.open(QIODevice::WriteOnly);
        file.write(m_DownloadedData);
        file.close();
        break;
    }

    default:
        break;
    }

    //emit a signal
    pReply->deleteLater();
    emit downloaded();
//    Q_EMIT downloaded();
}

QByteArray FileDownloader::downloadedData() const {
    return m_DownloadedData;
}
