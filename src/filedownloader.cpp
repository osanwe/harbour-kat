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

FileDownloader::~FileDownloader() {
}

void FileDownloader::startDownload(QString url, int mode) {
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
    qDebug() << "FileDownloader::fileDownloaded()";

    m_DownloadedData = pReply->readAll();
    writeDataToFile(buildFilePath());
    pReply->deleteLater();
    emit downloaded();
}

QByteArray FileDownloader::downloadedData() const {
    return m_DownloadedData;
}

QString FileDownloader::buildFilePath() {
    qDebug() << QString("FileDownloader::buildFilePath()");

    QString pathToFile;

    QStringList location = QStandardPaths::standardLocations(m_Mode == SAVING_TO_CACHE ?
                                                                 QStandardPaths::CacheLocation :
                                                                 QStandardPaths::DownloadLocation);

    if (location.isEmpty()) {
        QString envVariable = getenv(m_Mode == SAVING_TO_CACHE ?
                                         "$XDG_CACHE_HOME/harbour-kat/" : "$HOME/Downloads/");
        pathToFile = QString("%1/%2").arg(envVariable, m_FileName);
    } else pathToFile = QString("%1/%2").arg(location.first(), m_FileName);

    return pathToFile;
}

void FileDownloader::writeDataToFile(QString pathToFile) {
    qDebug() << QString("FileDownloader::writeDataToFile(%1)").arg(pathToFile);

    QFile file(pathToFile);
    if (file.exists()) return;

    file.open(QIODevice::WriteOnly);
    file.write(m_DownloadedData);
    file.close();
}
