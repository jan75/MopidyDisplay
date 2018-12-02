// artistsearchresults.h++
#ifndef H_ARTISTSEARCHRESULTS
#define H_ARTISTSEARCHRESULTS
#include <QString>
#include <QAbstractListModel>
#include <QStringList>
#include "artist.h++"
#include "album.h++"
#include "track.h++"
#include <memory>
#include <iostream>
#include <set>

class ArtistSearchResults : public QAbstractTableModel {
    Q_OBJECT

    private:
        std::set<std::shared_ptr<Artist>> artistSet;

    public:
        ArtistSearchResults(QObject *parent = nullptr);

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        QVariant data(const QModelIndex &index, int role) const override;

        void addArtist(std::shared_ptr<Artist> &track);
        void clearItems();
};

#endif
