#ifndef LINK_H
#define LINK_H

#include <QJsonObject>
#include <QObject>

class Link : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString url READ url CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)

public:
    explicit Link(QObject *parent = 0);

    static Link* fromJsonObject(QJsonObject object);

    QString url() const;
    void setUrl(const QString &url);

    QString title() const;
    void setTitle(const QString &title);

private:
    QString _url;
    QString _title;
};

#endif // LINK_H
