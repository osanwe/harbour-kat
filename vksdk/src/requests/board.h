#ifndef BOARD_H
#define BOARD_H

#include <QObject>

#include "apirequest.h"

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = 0);
    ~Board();

    void setApi(ApiRequest *api);

    Q_INVOKABLE void getTopics(int groupId, int offset = 0);
    Q_INVOKABLE void getComments(int groupId, int topicId, int offset = 0);
    Q_INVOKABLE void createComment(int groupId, int topicId, QString message);

private:
    ApiRequest *_api;
};

#endif // BOARD_H
