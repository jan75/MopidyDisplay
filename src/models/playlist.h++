// playlist.hpp
#ifndef H_PLAYLIST
#define H_PLAYLIST
#include <QString>
#include <QAbstractListModel>
#include <QStringList>
#include <iostream>

class Playlist : public QAbstractListModel {
    Q_OBJECT

    private:
        QStringList stringList;

    public:
        Playlist(QObject *parent = nullptr);

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role) const override;

        void addItem(QString string);
        void addItems(std::vector<QString> string_vector);
        void clearItems();
};

#endif
