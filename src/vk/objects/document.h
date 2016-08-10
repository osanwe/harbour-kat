#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QJsonObject>
#include <QObject>
#include <QString>

#include <QDebug>

class Document : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int ownerId READ ownerId CONSTANT)
    Q_PROPERTY(int size READ size CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString url READ url CONSTANT)
    Q_PROPERTY(QString photo READ photo CONSTANT)
    Q_PROPERTY(bool hasPhoto READ hasPhoto CONSTANT)

public:
    explicit Document(QObject *parent = 0);

    static Document* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    int ownerId() const;
    void setOwnerId(int ownerId);

    int size() const;
    void setSize(int size);

    QString title() const;
    void setTitle(const QString &title);

    QString url() const;
    void setUrl(const QString &url);

    bool hasPhoto() const;
    QString photo() const;
    void setPhoto100(const QString &photo100);
    void setPhoto130(const QString &photo130);

private:
    int _id;
    int _ownerId;
    int _size;
    QString _title;
    QString _url;
    QString _photo100;
    QString _photo130;
};

#endif // DOCUMENT_H
