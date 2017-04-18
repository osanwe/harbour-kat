#include "board.h"

Board::Board(QObject *parent) : QObject(parent)
{}

Board::~Board()
{}

void Board::setApi(ApiRequest *api) {
    _api = api;
}

void Board::getTopics(int groupId, int offset) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("group_id", QString::number(abs(groupId)));
    query->addQueryItem("count", "100");
    if (offset != 0) query->addQueryItem("offset", QString::number(offset));
    _api->makeApiGetRequest("board.getTopics", query, ApiRequest::BOARD_GET_TOPICS);
}

void Board::getComments(int groupId, int topicId, int offset) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("group_id", QString::number(abs(groupId)));
    query->addQueryItem("topic_id", QString::number(topicId));
    query->addQueryItem("count", "100");
    query->addQueryItem("extended", "1");
    if (offset != 0) query->addQueryItem("offset", QString::number(offset));
    _api->makeApiGetRequest("board.getComments", query, ApiRequest::BOARD_GET_COMMENTS);
}

void Board::createComment(int groupId, int topicId, QString message) {
    QUrlQuery *query = new QUrlQuery();
    query->addQueryItem("group_id", QString::number(abs(groupId)));
    query->addQueryItem("topic_id", QString::number(topicId));
    query->addQueryItem("message", message);
    _api->makeApiGetRequest("board.createComment", query, ApiRequest::BOARD_CREATE_COMMENT);
}
