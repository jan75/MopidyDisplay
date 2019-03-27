// album.c++
#include "album.h++"

Album::Album(QString name, std::vector<std::shared_ptr<Artist>> album_artists) {
    this->name = name;
    this->album_artists = album_artists;
    calculate_object_hash();
}

void Album::set_name(QString name) {
    this->name = name;
    calculate_object_hash();
}

QString Album::get_name() {
    return this->name;
}

void Album::set_album_artists(std::vector<std::shared_ptr<Artist>> album_artists) {
    this->album_artists = album_artists;
    calculate_object_hash();
}

std::vector<std::shared_ptr<Artist>> Album::get_album_artists() {
    return this->album_artists;
}

void Album::set_tracks(std::vector<std::shared_ptr<Track>> tracks) {
    this->tracks = tracks;
    calculate_object_hash();
}

std::vector<std::shared_ptr<Track>> Album::get_tracks() {
    return this->tracks;
}

void Album::add_track(std::shared_ptr<Track> track) {
    this->tracks.push_back(track);
    calculate_object_hash();
}

/**
 * @brief Album::compare compares an Album object with another Album object
 * @param album
 * @return boolean false if albums are identical, else true
 */
bool Album::compare(Album album) {
    if(this->get_object_hash() == album.get_object_hash()) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief see Album::compare(Album album)
 * @param album
 * @return boolean false if albums are identical, else true
 */
bool Album::compare(std::shared_ptr<Album> album) {
    Album *tmpAlbum = album.get();
    return compare(*tmpAlbum);
}

std::size_t Album::get_object_hash() {
    if(this->object_hash != 0) {
        return this->object_hash;
    } else {
        calculate_object_hash();
        return this->object_hash;
    }
}

void Album::calculate_object_hash() {
    std::size_t tmp_hashval = 0;
    std::hash<std::string> string_hash_function;
    tmp_hashval += string_hash_function(this->name.toStdString());
    for(std::shared_ptr<Artist> artist: this->album_artists) {
        tmp_hashval += artist->get_object_hash();
    }
    for(std::shared_ptr<Track> track: this->tracks) {
        tmp_hashval += track->get_object_hash();
    }

    this->object_hash = tmp_hashval;
}
