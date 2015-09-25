#include "notificationhelper.h"
#include <QtDBus>

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

void NotificationHelper::activateLed(bool activate)
{
    QDBusMessage message = QDBusMessage::createMethodCall(
                "com.nokia.mce",
                "/com/nokia/mce/request",
                "com.nokia.mce.request",
                activate ? "req_led_pattern_activate" :
                           "req_led_pattern_deactivate");
    message.setArguments(QList<QVariant>() << "PatternCommunicationIM");
    QDBusConnection connection(QDBusConnection::systemBus());
    connection.send(message);
}

void NotificationHelper::timerEvent(QTimerEvent *event)
{
    notification.remove();
}
