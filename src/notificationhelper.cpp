#include "notificationhelper.h"
#include <QtDBus>

NotificationHelper::NotificationHelper(QObject *parent) :
    QObject(parent)
{
}

void NotificationHelper::sendNotification(const QString &body, const QString &summary, const bool close) {
    notification.setBody(body);
    notification.setSummary(summary);

    notification.publish();
    if (close) startTimer(3000);
}

void NotificationHelper::activateLed(bool activate) {
    sendNotification("", "Новые сообщения", false);

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

void NotificationHelper::timerEvent(QTimerEvent *event) {
    notification.remove();
}
