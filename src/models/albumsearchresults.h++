// albumsearchresults.h++
#ifndef H_ALBUMSEARCHRESULTS
#define H_ALBUMSEARCHRESULTS
#include <QString>
#include <QAbstractListModel>
#include <QStringList>
#include "artist.h++"
#include "album.h++"
#include "track.h++"
#include <memory>
#include <iostream>
#include <set>

class AlbumSearchResults : public QAbstractTableModel {
    Q_OBJECT

    private:
        std::vector<std::shared_ptr<Album>> albumList;

    public:
        AlbumSearchResults(QObject *parent = nullptr);

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        QVariant data(const QModelIndex &index, int role) const override;

        void addAlbum(std::shared_ptr<Album> &album);
        void clearItems();
};

#endif
