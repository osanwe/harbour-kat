#ifndef VIDEO_H
#define VIDEO_H

#include <QJsonObject>
#include <QObject>
#include <QString>

#include <QDebug>

class Video : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int ownerId READ ownerId CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString photo READ photo CONSTANT)
    Q_PROPERTY(QString video READ video CONSTANT)

public:
    explicit Video(QObject *parent = 0);

    static Video* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    int ownerId() const;
    void setOwnerId(int ownerId);

    QString title() const;
    void setTitle(const QString &title);

    void setPhoto130(const QString &photo130);
    void setPhoto320(const QString &photo320);
    void setPhoto640(const QString &photo640);
    QString photo() const;

    void setMp4240(const QString &mp4240);
    void setMp4360(const QString &mp4360);
    void setMp4480(const QString &mp4480);
    void setMp4720(const QString &mp4720);
    void setExternal(const QString &external);
    QString video() const;

private:
    int _id;
    int _ownerId;
    QString _title;
    QString _photo130;
    QString _photo320;
    QString _photo640;
    QString _mp4240;
    QString _mp4360;
    QString _mp4480;
    QString _mp4720;
    QString _external;
};

#endif // VIDEO_H
