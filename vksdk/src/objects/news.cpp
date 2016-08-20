#include "news.h"

News::News(QObject *parent) : QObject(parent)
{}

News::~News()
{}

News *News::fromJsonObject(QJsonObject object) {
//    qDebug() << object;
    News *news = new News();
    if (object.contains("post_id")) news->setId(object.value("post_id").toInt());
    if (object.contains("source_id")) news->setSourceId(object.value("source_id").toInt());
    if (object.contains("to_id")) news->setToId(object.value("to_id").toInt());
    if (object.contains("from_id")) news->setFromId(object.value("from_id").toInt());
    if (object.contains("date")) news->setDate(object.value("date").toInt());
    if (object.contains("text")) news->setText(object.value("text").toString());
    if (object.contains("copy_text")) news->setCopyText(object.value("copy_text").toString());
    if (object.contains("copy_history")) {
        QJsonArray history = object.value("copy_history").toArray();
//        News* repost = new News();
//        repost->initJsonObject(history.at(0).toObject());
        news->setRepost(history.at(0).toObject());
    }
    if (object.contains("comments")) {
        QJsonObject comments = object.value("comments").toObject();
        if (comments.contains("count")) news->setCommentsCount(comments.value("count").toInt());
    }
    if (object.contains("likes")) {
        QJsonObject likes = object.value("likes").toObject();
        if (likes.contains("count")) news->setLikesCount(likes.value("count").toInt());
        if (likes.contains("user_likes")) news->setUserLiked(likes.value("user_likes").toInt() == 1);
    }
    if (object.contains("reposts")) {
        QJsonObject reposts = object.value("reposts").toObject();
        if (reposts.contains("count")) news->setRepostsCount(reposts.value("count").toInt());
        if (reposts.contains("user_reposted")) news->setUserReposted(reposts.value("user_reposted").toInt() == 1);
    }
    if (object.contains("geo")) {
        QJsonObject geo = object.value("geo").toObject();
        QStringList coords = geo.value("coordinates").toString().split(" ");
        news->setGeoMap(coords.at(0).toDouble(), coords.at(1).toDouble());
        news->setGeoTile(coords.at(0).toDouble(), coords.at(1).toDouble());
    }
    if (object.contains("attachments")) {
        QJsonArray attachments = object.value("attachments").toArray();
        for (int index = 0; index < attachments.size(); ++index) {
            QJsonObject attachment = attachments.at(index).toObject();
            if (attachment.value("type").toString() == "photo") {
                news->addPhoto(Photo::fromJsonObject(attachment.value("photo").toObject()));
            } else if (attachment.value("type").toString() == "posted_photo") {
                news->addPhoto(Photo::fromJsonObject(attachment.value("photo").toObject()));
            } else if (attachment.value("type").toString() == "video") {
                news->addVideo(Video::fromJsonObject(attachment.value("video").toObject()));
            } else if (attachment.value("type").toString() == "audio") {
                news->addAudio(Audio::fromJsonObject(attachment.value("audio").toObject()));
            } else if (attachment.value("type").toString() == "doc") {
                news->addDocument(Document::fromJsonObject(attachment.value("doc").toObject()));
            } else if (attachment.value("type").toString() == "graffiti") {
                //
            } else if (attachment.value("type").toString() == "link") {
                //
            } else if (attachment.value("type").toString() == "note") {
                //
            } else if (attachment.value("type").toString() == "app") {
                //
            } else if (attachment.value("type").toString() == "poll") {
                //
            } else if (attachment.value("type").toString() == "page") {
                //
            } else if (attachment.value("type").toString() == "album") {
                //
            } else if (attachment.value("type").toString() == "photos_list") {
                news->addPhoto(Photo::fromJsonObject(attachment.value("photo").toObject()));
            } else if (attachment.value("type").toString() == "market") {
                //
            } else if (attachment.value("type").toString() == "market_album") {
                //
            }
        }
    }
    return news;
}

int News::id() const
{
    return _id;
}

void News::setId(int id)
{
    _id = id;
}

int News::sourceId() const
{
    return _sourceId;
}

void News::setSourceId(int sourceId)
{
    _sourceId = sourceId;
}

int News::toId() const
{
    return _toId;
}

void News::setToId(int toId)
{
    _toId = toId;
}

int News::fromId() const
{
    return _fromId;
}

void News::setFromId(int fromId)
{
    _fromId = fromId;
}

int News::date() const
{
    return _date;
}

void News::setDate(int date)
{
    _date = date;
}

QString News::text() const
{
    return _text;
}

void News::setText(const QString &text)
{
    _text = text;
}

QString News::geoTile() const
{
    return _geoTile;
}

void News::setGeoTile(double lat, double lon)
{
    _geoTile = QString("http://www.mapquestapi.com/staticmap/v4/getmap?key=AfRC0WKf0YDWjtNKyWuB3LCpdHUQeME6&size=400,200&zoom=18&center=%1,%2").arg(lat).arg(lon);
}

QString News::geoMap() const
{
    return _geoMap;
}

void News::setGeoMap(double lat, double lon)
{
    _geoMap = QString("http://www.openstreetmap.org/?mlat=%1&mlon=%2&zoom=19").arg(lat).arg(lon);
}

QVariant News::audios() const
{
    return QVariant::fromValue(_audios);
}

QList<QObject *> News::audiosList() const
{
    return _audios;
}

void News::addAudio(Audio *audio)
{
    _audios.append(audio);
}

QVariant News::documents() const
{
    return QVariant::fromValue(_documents);
}

QList<QObject *> News::documentsList() const
{
    return _documents;
}

void News::addDocument(Document *document)
{
    _documents.append(document);
}

QVariant News::photos() const
{
    return QVariant::fromValue(_photos);
}

QList<QObject *> News::photosList() const
{
    return _photos;
}

void News::addPhoto(Photo *photo)
{
    _photos.append(photo);
}

QVariant News::videos() const
{
    return QVariant::fromValue(_videos);
}

QList<QObject *> News::videosList() const
{
    return _videos;
}

void News::addVideo(Video *video)
{
    _videos.append(video);
}

QString News::copyText() const
{
    return _copyText;
}

void News::setCopyText(const QString &copyText)
{
    _copyText = copyText;
}

News *News::repost() const
{
    return News::fromJsonObject(_repost);
}

void News::setRepost(QJsonObject repost)
{
    _repost = repost;
}

int News::likesCount() const
{
    return _likesCount;
}

void News::setLikesCount(int likesCount)
{
    _likesCount = likesCount;
}

int News::repostsCount() const
{
    return _repostsCount;
}

void News::setRepostsCount(int repostsCount)
{
    _repostsCount = repostsCount;
}

int News::commentsCount() const
{
    return _commentsCount;
}

void News::setCommentsCount(int commentsCount)
{
    _commentsCount = commentsCount;
}

bool News::userLiked() const
{
    return _userLiked;
}

void News::setUserLiked(bool userLiked)
{
    _userLiked = userLiked;
}

bool News::userReposted() const
{
    return _userReposted;
}

void News::setUserReposted(bool userReposted)
{
    _userReposted = userReposted;
}

