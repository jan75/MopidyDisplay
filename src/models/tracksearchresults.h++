// tracksearchresults.h++
#ifndef H_TRACKSEARCHRESULTS
#define H_TRACKSEARCHRESULTS
#include <QString>
#include <QAbstractListModel>
#include <QStringList>
#include "track.h++"
#include <memory>
#include <iostream>

class TrackSearchResults : public QAbstractTableModel {
    Q_OBJECT

    private:
        std::vector<std::shared_ptr<Track>> trackList;

    public:
        TrackSearchResults(QObject *parent = nullptr);

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        QVariant data(const QModelIndex &index, int role) const override;

        void addTrack(std::shared_ptr<Track> &track);
        void addTracks(std::vector<std::shared_ptr<Track>> &track_list);
        void clearItems();
};

#endif
