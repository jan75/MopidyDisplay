// track.h++
#ifndef H_TRACK
#define H_TRACK
#include <QString>
#include <QSettings>
#include <QListWidgetItem>
#include <memory>
#include <iostream>
#include <json.h++>

class Artist;
class Album;

class Track {
    public:
        Track(QString title, std::shared_ptr<Album> album, std::vector<std::shared_ptr<Artist>> artists, int length, int track_number);

        void print();

        void set_title(QString title);
        void set_album(std::shared_ptr<Album> album);
        void set_artists(std::vector<std::shared_ptr<Artist>> artists);
        void set_length(int length);
        void set_track_number(int track_number);
        
        void add_artist(std::shared_ptr<Artist> artist);
        void remove_artist(std::shared_ptr<Artist> artist);

        QString get_title();
        std::shared_ptr<Album> get_album();
        std::vector<std::shared_ptr<Artist>> get_artists();
        int get_length();
        QString get_length_readable();
        int get_track_number();

        std::size_t get_object_hash();
        
    private:
        QString title;
        std::shared_ptr<Album> album;
        std::vector<std::shared_ptr<Artist>> artists;
        int length;
        QString length_readable;
        int track_number;
        bool use_album_artist;

        std::size_t object_hash;

        void calculate_object_hash();
        QString length_to_str(int length);
};

#endif
