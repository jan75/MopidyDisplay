// track.hpp
#ifndef H_TRACK
#define H_TRACK
#include <QString>
#include <iostream>

class Track {
    public:
        Track(std::string title, std::string album, std::string artist);
        Track(QString title, QString album, QString artist);
        
        void set_title();
        void set_album();
        void set_artist();
        
        QString get_title();
        QString get_album();
        QString get_artist();
        
    private:
        QString title;
        QString album;
        QString artist;
};

#endif
