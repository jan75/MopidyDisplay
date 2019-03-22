// albumsearchresults.c++
#include "albumsearchresults.h++"

AlbumSearchResults::AlbumSearchResults(QObject *parent) : QAbstractTableModel(parent) {

}

int AlbumSearchResults::rowCount(const QModelIndex&) const {
    return albumList.size();
}

int AlbumSearchResults::columnCount(const QModelIndex&) const {
    return 1;
}

QVariant AlbumSearchResults::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role != Qt::DisplayRole) {
        return QVariant();
    }

    if(orientation == Qt::Horizontal) {
        switch(section)  {
            case 0: return QStringLiteral("Artist");
            default: return QStringLiteral("Column %1").arg(section);
        }
    } else {
        return QVariant();
    }
}


QVariant AlbumSearchResults::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) {
        return QVariant();
    }

    if(index.row() >= rowCount()) {
        return QVariant();
    }

    if(role != Qt::DisplayRole) {
        return QVariant();
    }

    int row = index.row();
    int column = index.column();
    std::shared_ptr<Album> album = albumList.at(row);
    if(column == 0) {
        //return album->get_album_artists()->get_name();
        return album->get_name();
    } else {
        return QVariant();
    }
}

void AlbumSearchResults::addAlbum(std::shared_ptr<Album> &album) {
    for(std::shared_ptr<Album> tmpAlbum: albumList) {
        if(album->compare(tmpAlbum)) {
            return;
        }
    }

    int first = albumList.size();

    QModelIndex *qModelIndexParent = new QModelIndex();

    beginInsertRows(*qModelIndexParent, first, first);
    albumList.push_back(album);
    endInsertRows();

    delete qModelIndexParent;
}

void AlbumSearchResults::clearItems() {
    int last = albumList.size();

    QModelIndex *qModelIndexParent = new QModelIndex();

    beginRemoveRows(*qModelIndexParent, 0, last);
    albumList.clear();
    endRemoveRows();

    delete qModelIndexParent;
}
