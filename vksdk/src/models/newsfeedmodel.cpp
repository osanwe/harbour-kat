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
        return QVariant(_getTitle(_newsfeed.at(index.row())->sourceId()));

    case TextRole:
        return QVariant(_newsfeed.at(index.row())->text());

    case DateRole:
        return QVariant(_newsfeed.at(index.row())->date());

    case CommentsCountRole:
        return QVariant(_newsfeed.at(index.row())->commentsCount());

    case LikesCountRole:
        return QVariant(_newsfeed.at(index.row())->likesCount());

    case RepostsCountRole:
        return QVariant(_newsfeed.at(index.row())->repostsCount());

    case IsLikedRole:
        return QVariant(_newsfeed.at(index.row())->userLiked());

    case IsRepostedRole:
        return QVariant(_newsfeed.at(index.row())->userReposted());

    case AttachmentsRole:
        return QVariant();

    case FullPostRole:
        return QVariant::fromValue(_newsfeed.at(index.row()));

    case PostIdRole:
        return QVariant(_newsfeed.at(index.row())->id());

    case SourceIdRole:
        return QVariant(_newsfeed.at(index.row())->sourceId());

    default:
        return QVariant();
    }
}

bool NewsfeedModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid()) return false;

    switch (role) {
    case LikesCountRole:
        _newsfeed.at(index.row())->setLikesCount(value.toInt());
        break;

    case IsLikedRole:
        _newsfeed.at(index.row())->setUserLiked(value.toBool());
        break;

    default:
        return false;
    }

    emit dataChanged(index, index, QVector<int>() << role);

    return true;
}

QHash<int, QByteArray> NewsfeedModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[AvatarRole] = "avatarSource";
    roles[TitleRole] = "title";
    roles[TextRole] = "newsText";
    roles[DateRole] = "datetime";
    roles[CommentsCountRole] = "commentsCount";
    roles[LikesCountRole] = "likesCount";
    roles[RepostsCountRole] = "repostsCount";
    roles[IsLikedRole] = "isLiked";
    roles[IsRepostedRole] = "isReposted";
    roles[AttachmentsRole] = "attachments";
    roles[FullPostRole] = "wallpost";
    roles[PostIdRole] = "postId";
    roles[SourceIdRole] = "sourceId";
    return roles;
}

Qt::ItemFlags NewsfeedModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::ItemIsEnabled;
    return QAbstractListModel::flags(index) | Qt::ItemIsEnabled;
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

void NewsfeedModel::setNextFrom(QString value) {
    _nextFrom = value;
}

int NewsfeedModel::size() const {
    return _newsfeed.size();
}

QString NewsfeedModel::next() const {
    return _nextFrom;
}

QString NewsfeedModel::_getAvatarSource(const int id) const {
    if (id > 0) {
        foreach (User *user, _profiles) if (id == user->id()) return user->photo50();
    } else if (id < 0) {
        foreach (Group *group, _groups) if (id == group->id()) return group->photo50();
    }
    return "image://theme/icon-m-person";
}

QString NewsfeedModel::_getTitle(const int id) const {
    if (id > 0) {
        foreach (User *user, _profiles) if (id == user->id()) return QString("%1 %2").arg(user->firstName()).arg(user->lastName());
    } else if (id < 0) {
        foreach (Group *group, _groups) if (id == group->id()) return group->name();
    }
    return "";
}

