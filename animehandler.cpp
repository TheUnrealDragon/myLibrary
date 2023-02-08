#include "animehandler.h"

AnimeHandler::AnimeHandler(QObject *parent)
    : QObject{parent}
{

}

int AnimeHandler::getTotalCompleted() const
{
    QFile file("anime.json");
    file.open(QFile::ReadOnly);
    QByteArray arr = file.readAll();
    QJsonDocument document  = QJsonDocument::fromJson(arr);
    QJsonObject obj = document.object();
    QJsonArray jarr = obj["completed"].toArray();
    int index = jarr.count();
    qDebug() << "jarr count << " << index;
    return index;
}

std::map<int, AnimeHandler::animelist> AnimeHandler::getCompleted()
{
    std::map<int,animelist> completedlist;
    QFile file("anime.json");
    file.open(QFile::ReadOnly);
    QByteArray arr = file.readAll();
    QJsonDocument document  = QJsonDocument::fromJson(arr);
    QJsonObject obj = document.object();
    QJsonArray jarr = obj["completed"].toArray();
    int index = 0;
    for(auto i: jarr)
    {
        QJsonObject obj  = i.toObject();
        animelist list;
        list.name = obj["title"].toString().toStdString();
        qDebug() << QString("Title Found ") + QString::fromStdString(list.name);
        list.imagepath = obj["image"].toString().toStdString();
        list.dateadded = obj["dateadded"].toString().toStdString();
        list.rating = obj["rating"].toString().toStdString();
        list.myrating = obj["myrating"].toString().toStdString();
        completedlist.insert({index++,list});
    }
    return completedlist;
}

void AnimeHandler::handleSearchTitleList(QStringList list)
{

}

QVariantList AnimeHandler::searchTitle(QVariant variant)
{
    QString titlestring = variant.toString();
    qDebug() << "Title: " << variant.toString();
    QVariantList list;
    emit thisTrySignal();
    if(!nmaster)
    {
        nmaster = new NetworkMaster();
        //nmasterthread = new QThread();
        //nmaster->moveToThread(nmasterthread);
        connect(this,&AnimeHandler::listNMasterMALTitles,nmaster,&NetworkMaster::searchMALTitles);
        connect(this,&AnimeHandler::startNMasterMALGrant,nmaster,&NetworkMaster::startMalGrant);
        //emit startNMasterMALGrant();
        connect(nmaster,&NetworkMaster::gotSearchTitleList,this,&AnimeHandler::handleSearchTitleList);
   }
   emit listNMasterMALTitles(titlestring);
    return list;
}

void AnimeHandler::getList()
{
    qDebug() << "Getting the list";

}

void AnimeHandler::tester()
{
    qDebug() << "Hello World!";
}
