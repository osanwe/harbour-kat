#include "notificationhelper.h"

NotificationHelper::NotificationHelper(QObject *parent) :
    QObject(parent)
{
}

void NotificationHelper::sendNotification(const QString &body, const QString &summary)
{
    notification.setBody(body);
    notification.setSummary(summary);

    notification.publish();
    startTimer(3000);
}

void NotificationHelper::timerEvent(QTimerEvent *event)
{
    notification.remove();
}
