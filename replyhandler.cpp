#include "replyhandler.h"

void ReplyHandler::setPort(QString port)
{
   this->port = port;
}

ReplyHandler::ReplyHandler(QObject *parent)
    : QAbstractOAuthReplyHandler{parent}
{

}

QString ReplyHandler::callback() const
{
    QString str = "http://localhost:" + port;
    qDebug() << "Callback " << str;
    return str;
}

void ReplyHandler::networkReplyFinished(QNetworkReply *rep)
{
    qDebug() << "Received!";
    QByteArray arr = rep->readAll();
    qDebug() << arr;
}
