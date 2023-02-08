#ifndef ANIMECOMPLETEDMODEL_H
#define ANIMECOMPLETEDMODEL_H

#include <QAbstractListModel>
#include "animehandler.h"

class AnimeCompletedModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AnimeCompletedModel(QObject *parent = nullptr);
    enum {
        ImageRole = Qt::UserRole,
        TitleRole
    };
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int,QByteArray> roleNames() const override;
private:
     std::map<int,AnimeHandler::animelist> completedlist;
     AnimeHandler handler;
};

#endif // ANIMECOMPLETEDMODEL_H
