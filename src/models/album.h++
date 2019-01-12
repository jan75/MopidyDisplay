// album.h++
#ifndef H_ALBUM
#define H_ALBUM
#include <QString>
#include <QSettings>
#include <QListWidgetItem>
#include <memory>
#include <iostream>
#include <json.h++>
#include "artist.h++"
#include "track.h++"

class Album {
    public:
        Album(QString name, std::shared_ptr<Artist> album_artist);

        void set_name(QString name);
        QString get_name();
        void set_album_artist(std::shared_ptr<Artist> album_artist);
        std::shared_ptr<Artist> get_album_artist();
        void set_tracks(std::vector<std::shared_ptr<Track>> tracks);
        std::vector<std::shared_ptr<Track>> get_tracks();

        void add_track(std::shared_ptr<Track> track);

        bool compare(Album album);
        bool compare(std::shared_ptr<Album> album);
        
    private:
        QString name;
        std::shared_ptr<Artist> album_artist;
        std::vector<std::shared_ptr<Track>> tracks;
        //std::shared_ptr<Track> tracks;
};

#endif
