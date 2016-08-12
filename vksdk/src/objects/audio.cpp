#include "audio.h"

Audio::Audio(QObject *parent) : QObject(parent)
{}

Audio *Audio::fromJsonObject(QJsonObject object) {
    Audio *audio = new Audio();
    if (object.contains("id")) audio->setId(object.value("id").toInt());
    if (object.contains("owner_id")) audio->setOwnerId(object.value("owner_id").toInt());
    if (object.contains("duration")) audio->setDuration(object.value("duration").toInt());
    if (object.contains("artist")) audio->setArtist(object.value("artist").toString());
    if (object.contains("title")) audio->setTitle(object.value("title").toString());
    if (object.contains("url")) audio->setUrl(object.value("url").toString());
    return audio;
}

int Audio::id() const
{
    return _id;
}

void Audio::setId(int id)
{
    _id = id;
}

int Audio::ownerId() const
{
    return _ownerId;
}

void Audio::setOwnerId(int ownerId)
{
    _ownerId = ownerId;
}

int Audio::duration() const
{
    return _duration;
}

void Audio::setDuration(int duration)
{
    _duration = duration;
}

QString Audio::artist() const
{
    return _artist;
}

void Audio::setArtist(const QString &artist)
{
    _artist = artist;
}

QString Audio::title() const
{
    return _title;
}

void Audio::setTitle(const QString &title)
{
    _title = title;
}

QString Audio::url() const
{
    return _url;
}

void Audio::setUrl(const QString &url)
{
    _url = url;
}

