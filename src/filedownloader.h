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

#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>

#include <QObject>
#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QUrl>
#include <QStandardPaths>
#include <QStringList>

#define SAVING_TO_CACHE 0
#define SAVING_TO_DOWNLOADS 1

class FileDownloader : public QObject
{
    Q_OBJECT

public:
    explicit FileDownloader(QObject *parent = 0);
    virtual ~FileDownloader();
    QByteArray downloadedData() const;

signals:
    void downloaded();

public slots:
    void startDownload(QString url, int mode);
    bool clearCache();

private slots:
    void fileDownloaded(QNetworkReply* pReply);

private:
    int m_Mode;
    QString m_FileName;
    QNetworkAccessManager m_WebCtrl;
    QByteArray m_DownloadedData;

    QString buildFilePath();
    void writeDataToFile(QString pathToFile);
};

#endif // FILEDOWNLOADER_H
