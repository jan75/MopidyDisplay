// albumsearchresults.c++
#include "albumsearchresults.h++"

AlbumSearchResults::AlbumSearchResults(QObject *parent) : QAbstractTableModel(parent) {

}

int AlbumSearchResults::rowCount(const QModelIndex&) const {
    return albumSet.size();
}

int AlbumSearchResults::columnCount(const QModelIndex&) const {
    return 2;
}

QVariant AlbumSearchResults::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role != Qt::DisplayRole) {
        return QVariant();
    }

    if(orientation == Qt::Horizontal) {
        switch(section)  {
            case 0: return QStringLiteral("Icon");
            case 1: return QStringLiteral("Title");
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
    std::shared_ptr<Album> album = *std::next(albumSet.begin(), row - 1);
    if(column == 0) {
        return "#";
    } else if(column == 1) {
        return album.get()->get_name();
    } else {
        return QVariant();
    }
}

void AlbumSearchResults::addAlbum(std::shared_ptr<Album> &album) {
    int first = albumSet.size();

    QModelIndex *qModelIndexParent = new QModelIndex();

    beginInsertRows(*qModelIndexParent, first, first);
    albumSet.insert(album);
    endInsertRows();

    delete qModelIndexParent;
}

void AlbumSearchResults::clearItems() {
    int last = albumSet.size();

    QModelIndex *qModelIndexParent = new QModelIndex();

    beginRemoveRows(*qModelIndexParent, 0, last);
    albumSet.clear();
    endRemoveRows();

    delete qModelIndexParent;
}
