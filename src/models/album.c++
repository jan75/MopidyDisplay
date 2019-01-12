// album.c++
#include "album.h++"

Album::Album(QString name, std::shared_ptr<Artist> album_artist) {
    this->name = name;
    this->album_artist = album_artist;
}

void Album::set_name(QString name) {
    this->name = name;
}

QString Album::get_name() {
    return this->name;
}

void Album::set_album_artist(std::shared_ptr<Artist> album_artist) {
    this->album_artist = album_artist;
}

std::shared_ptr<Artist> Album::get_album_artist() {
    return this->album_artist;
}

void Album::set_tracks(std::vector<std::shared_ptr<Track>> tracks) {
    this->tracks = tracks;
}

std::vector<std::shared_ptr<Track>> Album::get_tracks() {
    return this->tracks;
}

void Album::add_track(std::shared_ptr<Track> track) {
    this->tracks.push_back(track);
}

/**
 * @brief Album::compare compares an Album object with another Album object based on album name and album artist
 * @param album
 * @return boolean 1 if albums are identical, else 0
 */
bool Album::compare(Album album) {
    if(name == album.get_name() == true && album_artist->compare(album.get_album_artist()) == true) {
        return 1;
    }
    return 0;
}

/**
 * @brief see Album::compare(Album album)
 * @param album
 * @return boolean 1 if albums are identical, else 0
 */
bool Album::compare(std::shared_ptr<Album> album) {
    Album *tmpAlbum = album.get();
    return compare(*tmpAlbum);
}
