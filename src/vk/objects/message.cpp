#include "message.h"

Message::Message(QObject *parent) : QObject(parent)
{

}

Message *Message::fromJsonObject(QJsonObject object) {
    Message *message = new Message();
    message->setId(object.value("id").toInt());
    if (object.contains("user_id")) message->setUserId(object.value("user_id").toInt());
    if (object.contains("chat_id")) message->setChatId(object.value("chat_id").toInt());
    message->setFromId(object.value("from_id").toInt());
    message->setDate(object.value("date").toInt());
    message->setReadState(object.value("read_state").toBool());
    message->setOut(object.value("out").toBool());
    message->setBody(object.value("body").toString());
    if (object.contains("geo")) {
        QJsonObject geo = object.value("geo").toObject();
        QStringList coords = geo.value("coordinates").toString().split(" ");
        message->setGeo(QPair<QString, QString>(coords.at(0), coords.at(1)));
    }
    // Attachments
    if (object.contains("fwd_messages")) {
        QJsonArray fwds = object.value("fwd_messages").toArray();
        for (int index = 0; index < fwds.size(); ++index) {
            QJsonObject fwd = fwds.at(index).toObject();
            message->addFwdMessages(Message::fromJsonObject(fwd));
        }
    }
    return message;
}

int Message::id() const
{
    return _id;
}

void Message::setId(int id)
{
    _id = id;
}

int Message::chatId() const
{
    return _chatId;
}

void Message::setChatId(int chatId)
{
    _chatId = chatId;
}

int Message::fromId() const
{
    return _fromId;
}

void Message::setFromId(int fromId)
{
    _fromId = fromId;
}

int Message::date() const
{
    return _date;
}

void Message::setDate(int date)
{
    _date = date;
}

bool Message::readState() const
{
    return _readState;
}

void Message::setReadState(bool readState)
{
    _readState = readState;
}

bool Message::out() const
{
    return _out;
}

void Message::setOut(bool out)
{
    _out = out;
}

QString Message::body() const
{
    return _body;
}

void Message::setBody(const QString &body)
{
    _body = body;
}

QList<Message *> Message::fwdMessages() const
{
    return _fwdMessages;
}

void Message::addFwdMessages(Message *message)
{
    _fwdMessages.append(message);
}

int Message::userId() const
{
    return _userId;
}

void Message::setUserId(int userId)
{
    _userId = userId;
}

QPair<QString, QString> Message::geo() const
{
    return _geo;
}

void Message::setGeo(const QPair<QString, QString> &geo)
{
    _geo = geo;
}

