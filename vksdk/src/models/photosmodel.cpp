#include "photosmodel.h"

PhotosModel::PhotosModel(QObject *parent) : QAbstractListModel(parent)
{}

int PhotosModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return _photos.size();
}

QVariant PhotosModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    switch (role) {
    case IdRole:
        return QVariant(_photos.at(index.row())->id());
    case AlbumIdRole:
        return QVariant(_photos.at(index.row())->albumId());
    case OwnerIdRole:
        return QVariant(_photos.at(index.row())->ownerId());
    case UrlRole:
        return QVariant(_photos.at(index.row())->photoMaximum());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> PhotosModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[IdRole] = "photoId";
    roles[AlbumIdRole] = "photoAlbumId";
    roles[OwnerIdRole] = "photoOwnerId";
    roles[UrlRole] = "photoUrl";
    return roles;
}

void PhotosModel::clear() {
    beginRemoveRows(QModelIndex(), 0, _photos.size());
    _photos.clear();
    endRemoveRows();
    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

void PhotosModel::addPhoto(Photo *photo) {
    beginInsertRows(QModelIndex(), _photos.size(), _photos.size());
    _photos.append(photo);
    endInsertRows();

    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

int PhotosModel::getPhotoId(int index) {
    return _photos.at(index)->id();
}

int PhotosModel::getOwnerId(int index) {
    return _photos.at(index)->ownerId();
}

QString PhotosModel::getUrl(int index) {
    return _photos.at(index)->photoMaximum();
}

int PhotosModel::size() const {
    return _photos.size();
}

int PhotosModel::count() const {
    return _count;
}

void PhotosModel::setCount(int count) {
    _count = count;
}
