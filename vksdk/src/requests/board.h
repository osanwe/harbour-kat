#ifndef BOARD_H
#define BOARD_H

#include "requestbase.h"

class Board : public RequestBase
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = 0);

    Q_INVOKABLE void getTopics(int groupId, int offset = 0);
    Q_INVOKABLE void getComments(int groupId, int topicId, int offset = 0);
    Q_INVOKABLE void createComment(int groupId, int topicId, QString message);

};

#endif // BOARD_H
