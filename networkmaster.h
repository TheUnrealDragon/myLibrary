#ifndef NETWORKMASTER_H
#define NETWORKMASTER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QOAuth2AuthorizationCodeFlow>
#include <QAbstractOAuthReplyHandler>
#include <QSslSocket>
#include <QVariant>
#include <QVariantMap>
#include <QSslServer>
#include <QNetworkReply>
#include <QTcpServer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QUrlQuery>
#include "replyhandler.h"
#include <QTcpSocket>
#include <QDesktopServices>
#include <random>

class NetworkMaster : public QObject
{
    Q_OBJECT
public:
    explicit NetworkMaster(QObject *parent = nullptr);
    QVariantList getFromMALSearchTitles(QVariant title);
signals:
    void gotSearchTitleList(QStringList list);
public slots:
    void searchMALTitles(QString title);


    void malGranted();
    void startMalGrant();
    void sslServerMALPending();
    void sslSocketMALGetData();
    void malCallbackDataReceived(QByteArray arr);
    void malReplyTokensReceived(const QVariantMap &tokens);
    void malSearchTitleReplyFinished(QNetworkReply *r);
private:
    QTcpSocket *socket;
    QTcpServer *server;
    ReplyHandler *replyhandler;

    QNetworkAccessManager manager;
    QNetworkRequest globalrequest;
    QNetworkReply *globalreply;
    QOAuth2AuthorizationCodeFlow malflow;
};

#endif // NETWORKMASTER_H
