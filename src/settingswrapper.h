#ifndef SETTINGSWRAPPER_H
#define SETTINGSWRAPPER_H

#include <QObject>
#include <QSettings>
#include <QString>

class SettingsWrapper : public QObject
{
    Q_OBJECT

public:
    explicit SettingsWrapper(QObject *parent = 0);
    ~SettingsWrapper();

    Q_INVOKABLE void setAccessToken(QString value);
    Q_INVOKABLE void setDefaultPage(QString value);

    Q_INVOKABLE QString accessToken();
    Q_INVOKABLE QString defaultPage();

private:
    QSettings *_settings;

    const QString ACCESS_TOKEN_KEY = "accessToken";
    const QString DEFAULT_PAGE_KEY = "defaultPage";
};

#endif // SETTINGSWRAPPER_H
