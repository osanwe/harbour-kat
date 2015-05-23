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

void FileDownloader::fileDownloaded(QNetworkReply* pReply) {
    m_DownloadedData = pReply->readAll();

    switch (m_Mode) {
    case SAVING_TO_CACHE:
    {
        QString path("/home/nemo/.cache/harbour-kat/");
        QFile file(path.append(m_FileName));
        file.open(QIODevice::WriteOnly);
        file.write(m_DownloadedData);
        file.close();
        break;
    }

    case SAVING_TO_DOWNLOADS:
    {
        QString path("/home/nemo/Downloads/harbour-kat/");
        QFile file(path.append(m_FileName));
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
