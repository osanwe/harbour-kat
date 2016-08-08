#include "photo.h"

Photo::Photo(QObject *parent) : QObject(parent)
{}

Photo *Photo::fromJsonObject(QJsonObject object) {
    Photo *photo = new Photo();
    if (object.contains("id")) photo->setId(object.value("id").toInt());
    if (object.contains("album_id")) photo->setAlbumId(object.value("album_id").toInt());
    if (object.contains("owner_id")) photo->setOwnerId(object.value("owner_id").toInt());
    if (object.contains("text")) photo->setText(object.value("text").toString());
    if (object.contains("date")) photo->setDate(object.value("date").toInt());
    if (object.contains("photo_75")) photo->setPhoto75(object.value("photo_75").toString());
    if (object.contains("photo_130")) photo->setPhoto130(object.value("photo_130").toString());
    if (object.contains("photo_604")) photo->setPhoto604(object.value("photo_604").toString());
    if (object.contains("photo_807")) photo->setPhoto807(object.value("photo_807").toString());
    if (object.contains("photo_1280")) photo->setPhoto1280(object.value("photo_1280").toString());
    if (object.contains("photo_2560")) photo->setPhoto2560(object.value("photo_2560").toString());
    return photo;
}

int Photo::id() const
{
    return _id;
}

void Photo::setId(int id)
{
    _id = id;
}

int Photo::albumId() const
{
    return _albumId;
}

void Photo::setAlbumId(int albumId)
{
    _albumId = albumId;
}

int Photo::ownerId() const
{
    return _ownerId;
}

void Photo::setOwnerId(int ownerId)
{
    _ownerId = ownerId;
}

int Photo::date() const
{
    return _date;
}

void Photo::setDate(int date)
{
    _date = date;
}

QString Photo::text() const
{
    return _text;
}

void Photo::setText(const QString &text)
{
    _text = text;
}

void Photo::setPhoto75(const QString &photo75)
{
    _photo75 = photo75;
}

void Photo::setPhoto130(const QString &photo130)
{
    _photo130 = photo130;
}

void Photo::setPhoto604(const QString &photo604)
{
    _photo604 = photo604;
}

void Photo::setPhoto807(const QString &photo807)
{
    _photo807 = photo807;
}

void Photo::setPhoto1280(const QString &photo1280)
{
    _photo1280 = photo1280;
}

void Photo::setPhoto2560(const QString &photo2560)
{
    _photo2560 = photo2560;
}

QString Photo::photoMinimum() const {
    if (!_photo75.isEmpty()) return _photo75;
    if (!_photo130.isEmpty()) return _photo130;
    if (!_photo604.isEmpty()) return _photo604;
    if (!_photo807.isEmpty()) return _photo807;
    if (!_photo1280.isEmpty()) return _photo1280;
    if (!_photo2560.isEmpty()) return _photo2560;
}

QString Photo::photoMaximum() const {
    if (!_photo2560.isEmpty()) return _photo2560;
    if (!_photo1280.isEmpty()) return _photo1280;
    if (!_photo807.isEmpty()) return _photo807;
    if (!_photo604.isEmpty()) return _photo604;
    if (!_photo130.isEmpty()) return _photo130;
    if (!_photo75.isEmpty()) return _photo75;
}

