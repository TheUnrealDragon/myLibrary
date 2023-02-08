#ifndef ANIMEHANDLER_H
#define ANIMEHANDLER_H

#include <QObject>
#include <QDebug>
#include <map>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QThread>
#include "networkmaster.h"

class AnimeHandler : public QObject
{
    Q_OBJECT
public:
    struct animelist{
        std::string name;
        std::string imagepath;
        std::string dateadded;
        std::string rating;
        std::string myrating;
    };
    explicit AnimeHandler(QObject *parent = nullptr);
    int getTotalCompleted() const;
    int getTotalWatching();
    int getTotalDropped();
    std::map<int,animelist> getCompleted();
signals:
    void listNMasterMALTitles(QString title);
    void thisTrySignal();
    void startNMasterMALGrant();
public slots:
    void handleSearchTitleList(QStringList list);
    QVariantList searchTitle(QVariant variant);
    void getList();
    void tester();
private:
    NetworkMaster *nmaster = nullptr;
    QThread *nmasterthread = nullptr;
};

#endif // ANIMEHANDLER_H
