#ifndef MESSAGE_H
#define MESSAGE_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QPair>
#include <QString>
#include <QStringList>

class Message : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString body READ body CONSTANT)

public:
    explicit Message(QObject *parent = 0);

    static Message* fromJsonObject(QJsonObject object);

    int id() const;
    void setId(int id);

    int chatId() const;
    void setChatId(int chatId);

    int fromId() const;
    void setFromId(int fromId);

    int date() const;
    void setDate(int date);

    bool readState() const;
    void setReadState(bool readState);

    bool out() const;
    void setOut(bool out);

    QString body() const;
    void setBody(const QString &body);

    QList<Message *> fwdMessages() const;
    void addFwdMessages(Message *message);

    int userId() const;
    void setUserId(int userId);

    QPair<QString, QString> geo() const;
    void setGeo(const QPair<QString, QString> &geo);

private:
    int _id;
    int _userId;
    int _chatId;
    int _fromId;
    int _date;
    bool _readState;
    bool _out;
    QString _body;
    QPair<QString, QString> _geo;
    // Attachments
    QList<Message *> _fwdMessages;
};

#endif // MESSAGE_H
