#include "networkmaster.h"

NetworkMaster::NetworkMaster(QObject *parent)
    : QObject{parent}
{
}

QVariantList NetworkMaster::getFromMALSearchTitles(QVariant title)
{

}

void NetworkMaster::searchMALTitles(QString title)
{
    QNetworkRequest req;
    req.setRawHeader("X-MAL-CLIENT-ID","7a170c9786c828b4b026c9c0f26d5c91");
    QString titlequery = "q=" + title;
    QString sep = "&";
    QString limitquery = "limit=10";
    QUrlQuery queries;
    queries.addQueryItem("q",title);
    queries.addQueryItem("limit","10");
    QUrl url = QString("https://api.myanimelist.net/v2/anime") ;//+ titlequery + sep + limitquery;

    url.setQuery(queries);
    qDebug() << "Url with query:" << url.toDisplayString(QUrl::ComponentFormattingOption::EncodeSpaces);
    disconnect(&manager);
    connect(&manager,&QNetworkAccessManager::finished,this,&NetworkMaster::malSearchTitleReplyFinished);
    req.setUrl(url);
   manager.get(req);

}

void NetworkMaster::malGranted()
{
   qDebug() << "Granted MAL";
   QString req;
}

void NetworkMaster::startMalGrant()
{
    server = new QTcpServer();
    server->listen(QHostAddress::Any,45115);
    qDebug() << "Server Listening on port: " << server->serverPort();
    QString str = QString::number(server->serverPort());
    connect(server,&QTcpServer::pendingConnectionAvailable,this,&NetworkMaster::sslServerMALPending);
    malflow.setClientIdentifier("7a170c9786c828b4b026c9c0f26d5c91");
    malflow.setAccessTokenUrl(QUrl("https://myanimelist.net/v1/oauth2/token"));
    malflow.setNetworkAccessManager(&manager);
    malflow.setAuthorizationUrl(QUrl("https://myanimelist.net/v1/oauth2/authorize"));
    connect(&malflow,&QOAuth2AuthorizationCodeFlow::granted,this,&NetworkMaster::malGranted);

    qDebug() << "Generating a challenge code!";
    std::random_device r;

    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 66);
    QString challenge;
    do{
    int ranval = uniform_dist(e1);
//    qDebug() << "Randomly-chosen mean: " << ranval << '\n';
    //1-26 is A-Z
    char a = 0;
    if(ranval <=26)
    {
        a += 64;
        a += ranval;
        challenge += a;
    }
    else if(ranval >26 && ranval <=52)
    {
        ranval -= 26;
        a += 96;
        a += ranval;
        challenge += a;
    }
    else if(ranval >52 && ranval <= 62)
    {
        ranval -=52;
        a += 47;
        a += ranval;
        challenge += a;
    }
   /* else if(ranval == 63)
    {
        challenge += '-';
    }
    else if(ranval == 64)
    {
        challenge += '.';
    }*/
    else if(ranval == 65)
    {
        challenge += '_';
    }/*
    else if(ranval == 66)
    {
        challenge += '~';
    }*/
    }while(challenge.length() < 128);
    qDebug() << "random challenge=" << challenge;
    qDebug() << "Challenge length=" << challenge.length();
    replyhandler = new ReplyHandler();
    replyhandler->setPort(str);
    malflow.setReplyHandler(replyhandler);
     connect(&malflow, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);
    malflow.setModifyParametersFunction([challenge](QAbstractOAuth::Stage stage, QMultiMap<QString,QVariant> *map) {
            map->insert("code_challenge",QVariant(challenge));
         });
    connect(replyhandler,&QAbstractOAuthReplyHandler::tokensReceived,this,&NetworkMaster::malReplyTokensReceived);
    connect(replyhandler,&QAbstractOAuthReplyHandler::callbackDataReceived,this,&NetworkMaster::malCallbackDataReceived);
    qDebug() << malflow.authorizationUrl();
    qDebug() << malflow.accessTokenUrl();
    malflow.grant();
}

void NetworkMaster::sslServerMALPending()
{
    qDebug() << "Server got a new connection!";
   socket = server->nextPendingConnection();
   connect(socket,&QTcpSocket::readyRead,this,&NetworkMaster::sslSocketMALGetData);
}

void NetworkMaster::sslSocketMALGetData()
{
   QByteArray arr = socket->readAll();
   qDebug() << QString(arr);
}

void NetworkMaster::malCallbackDataReceived(QByteArray arr)
{
   qDebug() << "Callback Data received!";
   qDebug() << QString(arr);
}

void NetworkMaster::malReplyTokensReceived(const QVariantMap &tokens)
{
   qDebug() << "Tokens Receieved!";
   for(auto keys : tokens)
   {
       qDebug() << keys.toString();
   }
}

void NetworkMaster::malSearchTitleReplyFinished(QNetworkReply *r)
{
    QJsonDocument doc = QJsonDocument::fromJson(r->readAll());
    QJsonArray jarr = doc["data"].toArray();
    for(auto i : jarr)
    {
        QJsonObject obj = i.toObject();
        qDebug() << obj["node"].toObject()["title"].toString();
    }
}
