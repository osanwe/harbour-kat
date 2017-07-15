#ifndef GROUPS_H
#define GROUPS_H

#include "requestbase.h"

class Groups : public RequestBase
{
    Q_OBJECT
public:
    explicit Groups(QObject *parent = 0);

    Q_INVOKABLE void get(int userId = 0, int offset = 0);
    Q_INVOKABLE void getById(int groupId);
};

#endif // GROUPS_H
