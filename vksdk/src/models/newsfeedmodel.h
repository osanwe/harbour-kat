#ifndef NEWSFEEDMODEL_H
#define NEWSFEEDMODEL_H

#include <QAbstractListModel>
//#include <QObject>
//#include <QList>

#include "../objects/group.h"
#include "../objects/news.h"
#include "../objects/user.h"

//#include <QDebug>

class NewsfeedModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int size READ size CONSTANT)
    Q_PROPERTY(QString next READ next CONSTANT)

public:
    enum Roles {
        AvatarRole = Qt::UserRole + 1,
        TitleRole,
        TextRole,
        DateRole,
        CommentsCountRole,
        LikesCountRole,
        RepostsCountRole,
        IsLikedRole,
        IsRepostedRole,
        AttachmentsRole,
        FullPostRole,
        PostIdRole,
        SourceIdRole,
    };

    explicit NewsfeedModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual QHash<int, QByteArray> roleNames() const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    Q_INVOKABLE void clear();
    Q_INVOKABLE void addGroup(Group *group);
    Q_INVOKABLE void addNews(News *news);
    Q_INVOKABLE void addUser(User *user);
    Q_INVOKABLE void setNextFrom(QString value);

    int size() const;
    QString next() const;

private:
    QList<News *> _newsfeed;
    QHash<int, User*> _profiles;
    QHash<int, Group*> _groups;
//    QList<User *> _profiles;
//    QList<Group *> _groups;
    QString _nextFrom;

    QString _getAvatarSource(const int id) const;
    QString _getTitle(const int id) const;
};

#endif // NEWSFEEDMODEL_H
