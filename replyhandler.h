#ifndef REPLYHANDLER_H
#define REPLYHANDLER_H

#include <QAbstractOAuthReplyHandler>
#include <QObject>
#include <QNetworkReply>

class ReplyHandler : public QAbstractOAuthReplyHandler
{
    Q_OBJECT
    QString port;
public:
    void setPort(QString port);
    explicit ReplyHandler(QObject *parent = nullptr);
    QString callback() const;
public slots:
    void networkReplyFinished(QNetworkReply *reply);
};

#endif // REPLYHANDLER_H
