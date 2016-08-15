#ifndef NEWSFEEDMODEL_H
#define NEWSFEEDMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QList>

#include "../objects/group.h"
#include "../objects/news.h"
#include "../objects/user.h"

#include <QDebug>

class NewsfeedModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        AvatarRole = Qt::UserRole + 1,
        TitleRole,
        TextRole,
        DateRole,
        AttachmentsRole
    };

    explicit NewsfeedModel(QObject *parent = 0);
    ~NewsfeedModel();

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void addGroup(Group *group);
    Q_INVOKABLE void addNews(News *news);
    Q_INVOKABLE void addUser(User *user);

private:
    QList<News *> _newsfeed;
    QList<User *> _profiles;
    QList<Group *> _groups;

    QString _getAvatarSource(const int id) const;
};

#endif // NEWSFEEDMODEL_H
