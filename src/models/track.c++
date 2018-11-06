// track.c++
#include "track.h++"

Track::Track(QString title, QString album, QString artist, QListWidget *parent, int type) : QListWidgetItem(parent) {
    this->title = title;
    this->album = album;
    this->artist = artist;
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

void Track::print() {
    std::cout << this->title.toStdString() << " - " << this->album.toStdString() << " - " << this->artist.toStdString() << std::endl;
}
