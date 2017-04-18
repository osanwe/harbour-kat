#ifndef PHOTOSMODEL_H
#define PHOTOSMODEL_H


#include <QAbstractListModel>

#include "../objects/photo.h"


class PhotosModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ count CONSTANT)
    Q_PROPERTY(int size READ size CONSTANT)

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        AlbumIdRole,
        OwnerIdRole,
        UrlRole,
    };

    PhotosModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void clear();
    Q_INVOKABLE void addPhoto(Photo *photo);
    Q_INVOKABLE int getPhotoId(int index);
    Q_INVOKABLE int getOwnerId(int index);
    Q_INVOKABLE QString getUrl(int index);

    int size() const;
    int count() const;
    void setCount(int count);

private:
    QList<Photo *> _photos;
    int _count;
};

#endif // PHOTOSMODEL_H
