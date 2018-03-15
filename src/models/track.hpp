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
        void set_cover_path(QString cover_path);
        
        QString get_title();
        QString get_album();
        QString get_artist();
        QString get_cover_path();
        bool has_cover_path();
        
    private:
        QString title;
        QString album;
        QString artist;
        QString cover_path;
        bool cover_path_exists;
};

#endif
