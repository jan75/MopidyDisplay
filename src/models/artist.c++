// artist.c++
#include "artist.h++"

Artist::Artist(QString name) {
    this->name = name;
}

void Artist::set_name(QString name) {
    this->name = name;
    calculate_object_hash();
}

QString Artist::get_name() {
    return this->name;
}


/**
 * @brief Artist::compare compares an Artist object with another Artist object
 * @param artist
 * @return boolean 1 if artists are identical, else 0
 */
bool Artist::compare(Artist artist) {
    //std::cout << "Hash (this): " << this->object_hash << " Hash (other obj): " << artist.get_object_hash() << std::endl;
    if(this->object_hash == artist.get_object_hash()) {
        return 1;
    } else {
        return 0;
    }
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

std::size_t Artist::get_object_hash() {
    if(this->object_hash != 0) {
        return this->object_hash;
    } else {
        calculate_object_hash();
        return this->object_hash;
    }
}

void Artist::calculate_object_hash() {
    std::size_t tmp_hashval = 0;
    std::hash<std::string> string_hash_function;
    tmp_hashval = string_hash_function(this->name.toStdString());

    this->object_hash = tmp_hashval;
}

bool Artist::artist_compare(const std::shared_ptr<Artist> &a, const std::shared_ptr<Artist> &b) {
    //std::cout << a->compare(b) << std::endl;
    return a->compare(b);
}

