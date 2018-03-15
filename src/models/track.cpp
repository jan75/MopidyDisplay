// track.cpp
#include "track.hpp"

Track::Track(QString title, QString album, QString artist) {
    this->title = title;
    this->album = album;
    this->artist = artist;
    std::cout << "created 'Track' object with QString params" << std::endl;
}

Track::Track(std::string title, std::string album, std::string artist) {
    this->title = QString::fromStdString(title);
    this->album = QString::fromStdString(album);
    this->artist = QString::fromStdString(artist);
    std::cout << "created 'Track' object with string params" << std::endl;
}
