// track.h++
#ifndef H_TRACK
#define H_TRACK
#include <QString>
#include <QSettings>
#include <QListWidgetItem>
#include <memory>
#include <iostream>
#include <json.h++>

class Track {
    public:
        Track(QString title, QString album, QString artist, int length, int track_number);

        void print();

        void set_title(QString title);
        void set_album(QString album);
        void set_artist(QString artist);
        void set_length(int length);
        void set_track_number(int track_number);
        
        QString get_title();
        QString get_album();
        QString get_artist();
        int get_length();
        QString get_length_readable();
        int get_track_number();
        
    private:
        QString title;
        QString album;
        QString artist;
        int length;
        QString length_readable;
        int track_number;
        bool use_album_artist;

        QString length_to_str(int length);
};

#endif
