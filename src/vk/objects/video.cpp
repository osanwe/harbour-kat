#include "video.h"

Video::Video(QObject *parent) : QObject(parent)
{

}

Video *Video::fromJsonObject(QJsonObject object) {
    Video *video = new Video();
    if (object.contains("id")) video->setId(object.value("id").toInt());
    if (object.contains("owner_id")) video->setOwnerId(object.value("owner_id").toInt());
    if (object.contains("title")) video->setTitle(object.value("title").toString());
    if (object.contains("photo_130")) video->setPhoto130(object.value("photo_130").toString());
    if (object.contains("photo_320")) video->setPhoto320(object.value("photo_320").toString());
    if (object.contains("photo_640")) video->setPhoto640(object.value("photo_640").toString());
    if (object.contains("files")) {
        QJsonObject files = object.value("files").toObject();
        if (files.contains("mp4_240")) video->setMp4240(files.value("mp4_240").toString());
        if (files.contains("mp4_360")) video->setMp4360(files.value("mp4_360").toString());
        if (files.contains("mp4_480")) video->setMp4480(files.value("mp4_480").toString());
        if (files.contains("mp4_720")) video->setMp4720(files.value("mp4_720").toString());
        if (files.contains("external")) video->setExternal(files.value("external").toString());
    }
    return video;
}

int Video::id() const
{
    return _id;
}

void Video::setId(int id)
{
    _id = id;
}

int Video::ownerId() const
{
    return _ownerId;
}

void Video::setOwnerId(int ownerId)
{
    _ownerId = ownerId;
}

QString Video::title() const
{
    return _title;
}

void Video::setTitle(const QString &title)
{
    _title = title;
}

void Video::setPhoto130(const QString &photo130)
{
    _photo130 = photo130;
}

void Video::setPhoto320(const QString &photo320)
{
    _photo320 = photo320;
}

void Video::setPhoto640(const QString &photo640)
{
    _photo640 = photo640;
}

QString Video::photo() const
{
    if (!_photo640.isEmpty()) return _photo640;
    if (!_photo320.isEmpty()) return _photo320;
    return _photo130;
}

void Video::setMp4240(const QString &mp4240)
{
    _mp4240 = mp4240;
}

void Video::setMp4360(const QString &mp4360)
{
    _mp4360 = mp4360;
}

void Video::setMp4480(const QString &mp4480)
{
    _mp4480 = mp4480;
}

void Video::setMp4720(const QString &mp4720)
{
    _mp4720 = mp4720;
}

void Video::setExternal(const QString &external)
{
    _external = external;
}

QString Video::video() const
{
    if (!_external.isEmpty()) return _external;
    if (!_mp4720.isEmpty()) return _mp4720;
    if (!_mp4480.isEmpty()) return _mp4480;
    if (!_mp4360.isEmpty()) return _mp4360;
    return _mp4240;
}

