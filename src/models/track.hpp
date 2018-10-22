// track.hpp
#ifndef H_TRACK
#define H_TRACK
#include <QString>
#include <iostream>

class Track {
    public:
        Track(std::string title, std::string album, std::string artist);
        Track(QString title, QString album, QString artist);
        
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
};

#endif
