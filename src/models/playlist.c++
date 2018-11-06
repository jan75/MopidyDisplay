// playlist.c++
#include "playlist.h++"

Playlist::Playlist(QObject *parent) : QAbstractListModel(parent) {

}

int Playlist::rowCount(const QModelIndex &parent) const {
    return stringList.count();
}

QVariant Playlist::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) {
        return QVariant();
    }

    if(index.row() >= stringList.size()) {
        return QVariant();
    }

    if(role == Qt::DisplayRole) {
        return stringList.at(index.row());
    } else {
        return QVariant();
    }
}

void Playlist::addItem(QString string) {
    int first = stringList.count();
    int last = first + 1;

    QModelIndex *qModelIndexParent = new QModelIndex();

    beginInsertRows(*qModelIndexParent, first, last);
    stringList.append(string);
    endInsertRows();

    delete qModelIndexParent;
}

void Playlist::addItems(std::vector<QString> string_vector) {
    int first = stringList.count();
    int items = string_vector.size();
    int last = first + items;

    QModelIndex *qModelIndexParent = new QModelIndex();

    beginInsertRows(*qModelIndexParent, first, last);
    for(QString tmpString: string_vector) {
        stringList.append(tmpString);
    }
    endInsertRows();

    delete qModelIndexParent;
}

void Playlist::clearItems() {
    //int first = 1;
    int last = stringList.count();

    QModelIndex *qModelIndexParent = new QModelIndex();

    beginRemoveRows(*qModelIndexParent, 0, last);
    stringList.clear();
    endRemoveRows();

    delete qModelIndexParent;
}
