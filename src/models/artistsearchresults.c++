// artistsearchresults.c++
#include "artistsearchresults.h++"

ArtistSearchResults::ArtistSearchResults(QObject *parent) : QAbstractTableModel(parent) {

}

int ArtistSearchResults::rowCount(const QModelIndex&) const {
    return artistList.size();
}

int ArtistSearchResults::columnCount(const QModelIndex&) const {
    return 1;
}

QVariant ArtistSearchResults::headerData(int section, Qt::Orientation orientation, int role) const {
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
    std::shared_ptr<Artist> artist = artistList.at(row);
    if(column == 0) {
        return artist->get_name();
    } else {
        return QVariant();
    }
}


/**
 * @brief ArtistSearchResults::addArtist extends the search results with an artist object. Checks if the artist already exists.
 * If it already exists the artist is not added.
 * @param artist
 */
void ArtistSearchResults::addArtist(std::shared_ptr<Artist> &artist) {
    int first = artistList.size();

    QModelIndex *qModelIndexParent = new QModelIndex();

    beginInsertRows(*qModelIndexParent, first, first);
    artistList.push_back(artist);
    endInsertRows();

    delete qModelIndexParent;
}

void ArtistSearchResults::clearItems() {
    int last = artistList.size();

    QModelIndex *qModelIndexParent = new QModelIndex();

    beginRemoveRows(*qModelIndexParent, 0, last);
    artistList.clear();
    endRemoveRows();

    delete qModelIndexParent;
}
