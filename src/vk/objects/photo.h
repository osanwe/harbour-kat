#ifndef PHOTO_H
#define PHOTO_H

#include <QJsonObject>
#include <QObject>
#include <QString>

class Photo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString photoMinimum READ photoMinimum CONSTANT)
    Q_PROPERTY(QString photoMaximum READ photoMaximum CONSTANT)

public:
    explicit Photo(QObject *parent = 0);

    static Photo* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    int albumId() const;
    void setAlbumId(int albumId);

    int ownerId() const;
    void setOwnerId(int ownerId);

    int date() const;
    void setDate(int date);

    QString text() const;
    void setText(const QString &text);

    void setPhoto75(const QString &photo75);
    void setPhoto130(const QString &photo130);
    void setPhoto604(const QString &photo604);
    void setPhoto807(const QString &photo807);
    void setPhoto1280(const QString &photo1280);
    void setPhoto2560(const QString &photo2560);
    Q_INVOKABLE QString photoMinimum() const;
    Q_INVOKABLE QString photoMaximum() const;

private:
    int _id;
    int _albumId;
    int _ownerId;
    int _date;
    QString _text;
    QString _photo75;
    QString _photo130;
    QString _photo604;
    QString _photo807;
    QString _photo1280;
    QString _photo2560;
};

#endif // PHOTO_H
