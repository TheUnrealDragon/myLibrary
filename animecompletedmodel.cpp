#include "animecompletedmodel.h"

AnimeCompletedModel::AnimeCompletedModel(QObject *parent)
    : QAbstractListModel(parent)
{
    completedlist = handler.getCompleted();
}

int AnimeCompletedModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
   return handler.getTotalCompleted() ;
}

QVariant AnimeCompletedModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    // FIXME: Implement me!
       AnimeHandler::animelist list = completedlist.at(index.row() );
       switch(role){
        case ImageRole:
            {
                return QVariant(QString::fromStdString(list.imagepath));
            }
        case TitleRole:
            return QVariant(QString::fromStdString(list.name));
      }
    return QVariant();
}

bool AnimeCompletedModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags AnimeCompletedModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> AnimeCompletedModel::roleNames() const
{
    QHash<int, QByteArray> hash;
    hash[ImageRole] = "imagepath";
    hash[TitleRole] = "title";
    return hash;
}
