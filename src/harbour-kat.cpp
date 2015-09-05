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

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QGuiApplication>
#include <QScopedPointer>
#include <QQuickView>
#include <QQmlContext>

#include <QUrl>
#include <QStandardPaths>
#include <QStringList>

#include "filedownloader.h"
#include "notificationhelper.h"
#include "api/photos.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    QScopedPointer<FileDownloader> fileDownloader(new FileDownloader(view.data()));
    QScopedPointer<NotificationHelper> notificationHelper(new NotificationHelper(view.data()));
    QScopedPointer<Photos> photos(new Photos(view.data()));

    QUrl cachePath;
    QStringList cacheLocation = QStandardPaths::standardLocations(QStandardPaths::CacheLocation);
    if (cacheLocation.isEmpty()) cachePath = getenv("$XDG_CACHE_HOME/harbour-kat/");
    else cachePath = QString("%1/").arg(cacheLocation.first());

    view->rootContext()->setContextProperty("cachePath", cachePath);
    view->rootContext()->setContextProperty("fileDownloader", fileDownloader.data());
    view->rootContext()->setContextProperty("notificationHelper", notificationHelper.data());
    view->rootContext()->setContextProperty("photos", photos.data());

    view->setSource(SailfishApp::pathTo("qml/harbour-kat.qml"));
    view->show();

    return application->exec();
}

