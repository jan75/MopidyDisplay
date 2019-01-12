// artist.c++
#include "artist.h++"

Artist::Artist(QString name) {
    this->name = name;
}

void Artist::set_name(QString name) {
    this->name = name;
}

QString Artist::get_name() {
    return this->name;
}


/**
 * @brief Artist::compare compares an Artist object with another Artist object based on artist name
 * @param artist
 * @return boolean 1 if artists are identical, else 0
 */
bool Artist::compare(Artist artist) {
    if(name == artist.get_name()) {
        return 1;
    }
    return 0;
}

/**
 * @brief see Artist::compare(Artist artist)
 * @param artist
 * @return boolean 1 if artists are identical, else 0
 */
bool Artist::compare(std::shared_ptr<Artist> artist) {
    Artist *tmpArtist = artist.get();
    return compare(*tmpArtist);
}

