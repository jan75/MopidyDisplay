// searchresults.h++
#ifndef H_SEARCHRESULTS
#define H_SEARCHRESULTS
#include <QString>
#include <QSettings>
#include <QListWidgetItem>
#include <memory>
#include <iostream>
#include <set>
#include <json.h++>
#include "artist.h++"
#include "album.h++"
#include "track.h++"

class SearchResults {
    public:
        SearchResults(std::set<std::shared_ptr<Artist>> artists, std::set<std::shared_ptr<Album>> albums, std::set<std::shared_ptr<Track>> tracks);
        SearchResults();

        void set_artists(std::set<std::shared_ptr<Artist>> artists);
        void set_albums(std::set<std::shared_ptr<Album>> albums);
        void set_tracks(std::set<std::shared_ptr<Track>> tracks);

        std::set<std::shared_ptr<Artist>> get_artists();
        std::set<std::shared_ptr<Album>> get_albums();
        std::set<std::shared_ptr<Track>> get_tracks();

        bool add_artist(std::shared_ptr<Artist> artist);
        bool add_album(std::shared_ptr<Album> album);
        bool add_track(std::shared_ptr<Track> track);

        bool remove_artist(std::shared_ptr<Artist> artist);
        bool remove_album(std::shared_ptr<Album> album);
        bool remove_track(std::shared_ptr<Track> track);
        
    private:
        std::set<std::shared_ptr<Artist>> artists;
        std::set<std::shared_ptr<Album>> albums;
        std::set<std::shared_ptr<Track>> tracks;
};

#endif
