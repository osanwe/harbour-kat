#ifndef NOTIFICATIONHELPER_H
#define NOTIFICATIONHELPER_H

#include <QObject>

#include "mlite5/MNotification"

class NotificationHelper : public QObject
{
    Q_OBJECT
public:
    explicit NotificationHelper(QObject *parent = 0);

    Q_INVOKABLE void sendNotification(const QString &body, const QString &summary);
    Q_INVOKABLE void activateLed();

signals:

public slots:

protected:
    void timerEvent(QTimerEvent *event);

private:
    MNotification notification;
};

#endif // NOTIFICATIONHELPER_H
