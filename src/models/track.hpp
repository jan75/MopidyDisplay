// track.hpp
#ifndef H_TRACK
#define H_TRACK
#include <QString>
#include <QSettings>
#include <iostream>
#include <json.hpp>

class Track {
    public:
        Track(std::string title, std::string album, std::string artist);
        Track(QString title, QString album, QString artist);
        
        static Track parse_mopidy_track_model(nlohmann::json json);
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
