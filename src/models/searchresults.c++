// searchresults.c++
#include "searchresults.h++"

SearchResults::SearchResults(std::set<std::shared_ptr<Artist>> artists, std::set<std::shared_ptr<Album>> albums, std::set<std::shared_ptr<Track>> tracks) {
    this->artists = artists;
    this->albums = albums;
    this->tracks = tracks;
}

SearchResults::SearchResults() {

}

void SearchResults::set_artists(std::set<std::shared_ptr<Artist>> artists) {
    this->artists = artists;
}

void SearchResults::set_albums(std::set<std::shared_ptr<Album>> albums) {
    this->albums = albums;
}

void SearchResults::set_tracks(std::set<std::shared_ptr<Track>> tracks) {
    this->tracks = tracks;
}

std::set<std::shared_ptr<Artist>> SearchResults::get_artists() {
    return this->artists;
}

std::set<std::shared_ptr<Album>> SearchResults::get_albums() {
    return this->albums;
}

std::set<std::shared_ptr<Track>> SearchResults::get_tracks() {
    return this->tracks;
}


/**
 * @brief SearchResults::add_artist add an Artist object to the set
 *
 * The return function of std::set::insert returns a pair of iterator and boolean.
 * Since this is an insert function the iterator is not needed and the second value
 * in the pair is returned, which is a boolean. This boolean shows if the value has
 * been added or not (values in sets are unique).
 *
 * @param artist
 * @return bool true if insert successful, otherwise false
 */
bool SearchResults::add_artist(std::shared_ptr<Artist> artist) {
    return artists.insert(artist).second;
}

/**
 * @brief SearchResults::add_album add an Album object to the set
 *
 * The return function of std::set::insert returns a pair of iterator and boolean.
 * Since this is an insert function the iterator is not needed and the second value
 * in the pair is returned, which is a boolean. This boolean shows if the value has
 * been added or not (values in sets are unique).
 *
 * @param album
 * @return bool true if insert successful, otherwise false
 */
bool SearchResults::add_album(std::shared_ptr<Album> album) {
    return albums.insert(album).second;
}

/**
 * @brief SearchResults::add_track add a Track object to the set
 *
 * The return function of std::set::insert returns a pair of iterator and boolean.
 * Since this is an insert function the iterator is not needed and the second value
 * in the pair is returned, which is a boolean. This boolean shows if the value has
 * been added or not (values in sets are unique).
 *
 * @param track
 * @return bool true if insert successful, otherwise false
 */
bool SearchResults::add_track(std::shared_ptr<Track> track) {
    return tracks.insert(track).second;
}


/**
 * @brief SearchResults::remove_artist remove Artist object
 * @param artist
 * @return bool true if removal successful, otherwise false
 */
bool SearchResults::remove_artist(std::shared_ptr<Artist> artist) {
    return artists.erase(artist);
}

/**
 * @brief SearchResults::remove_album remove Album object
 * @param album
 * @return bool true if removal successful, otherwise false
 */
bool SearchResults::remove_album(std::shared_ptr<Album> album) {
    return albums.erase(album);
}

/**
 * @brief SearchResults::remove_track remove Track object
 * @param track
 * @return bool true if removal successful, otherwise false
 */
bool SearchResults::remove_track(std::shared_ptr<Track> track) {
    return tracks.erase(track);
}
