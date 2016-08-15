#include "newsfeedmodel.h"

NewsfeedModel::NewsfeedModel(QObject *parent) : QAbstractListModel(parent)
{}

NewsfeedModel::~NewsfeedModel()
{}

int NewsfeedModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return _newsfeed.size();
}

QVariant NewsfeedModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) return QVariant();

    switch (role) {
    case AvatarRole:
        return QVariant(_getAvatarSource(_newsfeed.at(index.row())->sourceId()));

    case TitleRole:
        return QVariant();

    case TextRole:
        return QVariant(_newsfeed.at(index.row())->text());

    case DateRole:
        return QVariant(_newsfeed.at(index.row())->date());

    case AttachmentsRole:
        return QVariant();

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> NewsfeedModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[AvatarRole] = "avatarSource";
    roles[TitleRole] = "title";
    roles[TextRole] = "newsText";
    roles[DateRole] = "datetime";
    roles[AttachmentsRole] = "attachments";
    return roles;
}

void NewsfeedModel::addGroup(Group *group) {
    _groups.append(group);
    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

void NewsfeedModel::addNews(News *news) {
    beginInsertRows(QModelIndex(), _newsfeed.size(), _newsfeed.size());
    _newsfeed.append(news);
    endInsertRows();
    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

void NewsfeedModel::addUser(User *user) {
    _profiles.append(user);
    QModelIndex index = createIndex(0, 0, static_cast<void *>(0));
    emit dataChanged(index, index);
}

QString NewsfeedModel::_getAvatarSource(const int id) const {
    if (id > 0) {
        foreach (User *user, _profiles) if (id == user->id()) return user->photo50();
    } else if (id < 0) {
        foreach (Group *group, _groups) if (id == group->id()) return group->photo50();
    }
    return "image://theme/icon-m-person";
}

