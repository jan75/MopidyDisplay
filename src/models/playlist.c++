// playlist.c++
#include "playlist.h++"

Playlist::Playlist(QObject *parent) : QAbstractTableModel(parent) {

}

int Playlist::rowCount(const QModelIndex&) const {
    return trackList.size();
}

int Playlist::columnCount(const QModelIndex&) const {
    return 3;
}

QVariant Playlist::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role != Qt::DisplayRole) {
        return QVariant();
    }

    if(orientation == Qt::Horizontal) {
        switch(section)  {
            case 0: return QStringLiteral("#");
            case 1: return QStringLiteral("Title");
            case 2: return QStringLiteral("Length");
            default: return QStringLiteral("Column %1").arg(section);
        }
    } else {
        return QVariant();
    }
}


QVariant Playlist::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) {
        return QVariant();
    }

    if(index.row() >= trackList.size()) {
        return QVariant();
    }

    if(role != Qt::DisplayRole) {
        return QVariant();
    }

    std::shared_ptr<Track> track = trackList.at(index.row());
    if(index.column() == 0) {
        return track.get()->get_track_number();
        //return QVariant::fromValue(track.get()->get_title());
    } else if(index.column() == 1) {
        return track.get()->get_title();
        //return QVariant::fromValue(track.get()->get_artist());
    } else if(index.column() == 2) {
        return track.get()->get_length_readable();
    } else {
        return QVariant();
    }
}

void Playlist::addTrack(std::shared_ptr<Track> &track) {
    int first = trackList.size();

    std::cout << "size: " << trackList.size() << std::endl;

    QModelIndex *qModelIndexParent = new QModelIndex();

    std::cout << track.get()->get_title().toStdString() << std::endl;

    beginInsertRows(*qModelIndexParent, first, first);
    trackList.push_back(track);
    endInsertRows();

    std::cout << "size: " << trackList.size() << std::endl;

    delete qModelIndexParent;
}

void Playlist::addTracks(std::vector<std::shared_ptr<Track>> &track_list) {
    int first = trackList.size();
    int items = track_list.size();
    int last = first + items;

    QModelIndex *qModelIndexParent = new QModelIndex();

    beginInsertRows(*qModelIndexParent, first, last);
    trackList.reserve(last);
    trackList.insert(trackList.end(), track_list.begin(), track_list.end());
    endInsertRows();

    delete qModelIndexParent;
}

void Playlist::clearItems() {
    int last = trackList.size();

    QModelIndex *qModelIndexParent = new QModelIndex();

    beginRemoveRows(*qModelIndexParent, 0, last);
    trackList.clear();
    endRemoveRows();
    std::cout << trackList.size() << std::endl;

    delete qModelIndexParent;
}
