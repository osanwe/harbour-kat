/*
  Copyright (C) 2016 Petr Vytovtov
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

#ifndef GROUP_H
#define GROUP_H

#include <QJsonObject>
#include <QObject>
#include <QString>

#include <QDebug>

class Group : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString status READ status CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)
    Q_PROPERTY(QString photo50 READ photo50 CONSTANT)
    Q_PROPERTY(QString photo100 READ photo100 CONSTANT)
    Q_PROPERTY(QString photo200 READ photo200 CONSTANT)
    Q_PROPERTY(int membersCount READ membersCount CONSTANT)
    Q_PROPERTY(int photosCount READ photosCount CONSTANT)
    Q_PROPERTY(int audiosCount READ audiosCount CONSTANT)
    Q_PROPERTY(int videosCount READ videosCount CONSTANT)
    Q_PROPERTY(int topicsCount READ topicsCount CONSTANT)
    Q_PROPERTY(int docsCount READ docsCount CONSTANT)

public:
    explicit Group(QObject *parent = 0);

    static Group* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString photo50() const;
    void setPhoto50(const QString &photo50);

    QString photo100() const;
    void setPhoto100(const QString &photo100);

    QString photo200() const;
    void setPhoto200(const QString &photo200);

    QString status() const;
    void setStatus(const QString &status);

    QString description() const;
    void setDescription(const QString &description);

    int photosCount() const;
    void setPhotosCount(int photosCount);

    int audiosCount() const;
    void setAudiosCount(int audiosCount);

    int videosCount() const;
    void setVideosCount(int videosCount);

    int topicsCount() const;
    void setTopicsCount(int topicsCount);

    int docsCount() const;
    void setDocsCount(int docsCount);

    int membersCount() const;
    void setMembersCount(int membersCount);

private:
    int _id;
    QString _name;
    QString _status;
    QString _description;
    QString _photo50;
    QString _photo100;
    QString _photo200;
    int _membersCount = 0;
    int _photosCount = 0;
    int _audiosCount = 0;
    int _videosCount = 0;
    int _topicsCount = 0;
    int _docsCount = 0;
};

#endif // GROUP_H
