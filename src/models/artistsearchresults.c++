// artistsearchresults.c++
#include "artistsearchresults.h++"

ArtistSearchResults::ArtistSearchResults(QObject *parent) : QAbstractTableModel(parent) {

}

int ArtistSearchResults::rowCount(const QModelIndex&) const {
    return artistSet.size();
}

int ArtistSearchResults::columnCount(const QModelIndex&) const {
    return 2;
}

QVariant ArtistSearchResults::headerData(int section, Qt::Orientation orientation, int role) const {
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


QVariant ArtistSearchResults::data(const QModelIndex &index, int role) const {
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
    std::shared_ptr<Artist> artist = *std::next(artistSet.begin(), row - 1);
    if(column == 0) {
        return "#";
    } else if(column == 1) {
        return artist.get()->get_name();
    } else {
        return QVariant();
    }
}

void ArtistSearchResults::addArtist(std::shared_ptr<Artist> &artist) {
    int first = artistSet.size();

    QModelIndex *qModelIndexParent = new QModelIndex();

    beginInsertRows(*qModelIndexParent, first, first);
    artistSet.insert(artist);
    endInsertRows();

    delete qModelIndexParent;
}

void ArtistSearchResults::clearItems() {
    int last = artistSet.size();

    QModelIndex *qModelIndexParent = new QModelIndex();

    beginRemoveRows(*qModelIndexParent, 0, last);
    artistSet.clear();
    endRemoveRows();

    delete qModelIndexParent;
}
