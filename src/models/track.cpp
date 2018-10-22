// track.cpp
#include "track.hpp"

Track::Track(QString title, QString album, QString artist) {
    this->title = title;
    this->album = album;
    this->artist = artist;
}

Track::Track(std::string title, std::string album, std::string artist) {
    this->title = QString::fromStdString(title);
    this->album = QString::fromStdString(album);
    this->artist = QString::fromStdString(artist);
}

void Track::set_title(QString title) {
    this->title = title;
}

void Track::set_album(QString album) {
    this->album = album;
}

void Track::set_artist(QString artist) {
    this->artist = artist;
}

QString Track::get_title() {
    return this->title;
}

QString Track::get_album() {
    return this->album;
}

QString Track::get_artist() {
    return this->artist;
}
