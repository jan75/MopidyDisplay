// track.hpp
#ifndef H_TRACK
#define H_TRACK
#include <QString>
#include <QSettings>
#include <QListWidgetItem>
#include <memory>
#include <iostream>
#include <json.h++>

class Track : public QListWidgetItem {
    public:
        Track(QString title, QString album, QString artist, QListWidget *parent = nullptr, int type = Type);
        //Track(QString title, QString album, QString artist, QObject *parent = 0);
        
        void print();

        void set_title(QString title);
        void set_album(QString album);
        void set_artist(QString artist);
        
        QString get_title();
        QString get_album();
        QString get_artist();
        
    private:
        QString title;
        QString album;
        QString artist;
        bool use_album_artist;
};

#endif
