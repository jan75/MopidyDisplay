// album.h++
#ifndef H_ALBUM
#define H_ALBUM
#include <QString>
#include <QSettings>
#include <QListWidgetItem>
#include <memory>
#include <iostream>
#include <functional>
#include <json.h++>
#include "artist.h++"
#include "track.h++"

class Album {
    public:
        Album(QString name, std::vector<std::shared_ptr<Artist>> album_artists);

        void set_name(QString name);
        QString get_name();
        void set_album_artists(std::vector<std::shared_ptr<Artist>> album_artists);
        std::vector<std::shared_ptr<Artist>> get_album_artists();
        void set_tracks(std::vector<std::shared_ptr<Track>> tracks);
        std::vector<std::shared_ptr<Track>> get_tracks();

        void add_track(std::shared_ptr<Track> track);

        std::size_t get_object_hash();

        bool compare(Album album);
        bool compare(std::shared_ptr<Album> album);

        static bool album_compare(const std::shared_ptr<Album> &a, const std::shared_ptr<Album> &b);
        
    private:
        QString name;
        std::size_t object_hash;
        std::vector<std::shared_ptr<Artist>> album_artists;
        std::vector<std::shared_ptr<Track>> tracks;

        void calculate_object_hash();
};

#endif
