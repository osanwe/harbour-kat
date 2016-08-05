#ifndef DIALOG_H
#define DIALOG_H

#include <QJsonObject>
#include <QObject>

#include "message.h"

class Dialog : public QObject
{
    Q_OBJECT

public:
    explicit Dialog(QObject *parent = 0);

    static Dialog *fromJsonObject(QJsonObject object);

private:
    bool _unread;
    Message *_lastMessage;
};

#endif // DIALOG_H
