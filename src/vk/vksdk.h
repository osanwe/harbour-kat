#ifndef VKSDK_H
#define VKSDK_H

#include <QObject>
#include <QString>

class VkSDK : public QObject
{
    Q_OBJECT

public:
    explicit VkSDK(QObject *parent = 0);
    ~VkSDK();

    Q_INVOKABLE void setAccessTocken(QString value);

private:
    QString _accessToken;
};

#endif // VKSDK_H
