// track.cpp
#include "track.hpp"

Track::Track(QString title, QString album, QString artist) {
    /*
    QSettings settings("metasoft", "mopidydisplay");
    settings.beginGroup("general");
    this->use_album_artist = settings.value("use-album-artist", true).toBool();
    settings.endGroup();
    */

    this->title = title;
    this->album = album;
    this->artist = artist;
}

Track::Track(std::string title, std::string album, std::string artist) {
    QString titleQ = QString::fromStdString(title);
    QString albumQ = QString::fromStdString(album);
    QString artistQ = QString::fromStdString(artist);

    Track(titleQ, albumQ, artistQ);
}

Track Track::parse_mopidy_track_model(nlohmann::json json) {
    std::string title = json["name"];
    std::string album = json["album"]["name"];
    std::string artist;
    nlohmann::json artists = json["artists"];
    if(artists.size() > 1) {
        std::cout << "Multiple artists, picking first: " << artists[0]["name"] << std::endl;
    } else if(artists.size() == 0) {
        std::cout << "No artists found" << std::endl;
    } else {
        artist = artists[0]["name"];
    }

    QString titleQ = QString::fromStdString(title);
    QString albumQ = QString::fromStdString(album);
    QString artistQ = QString::fromStdString(artist);

    Track tmpTrack(titleQ, albumQ, artistQ);
    return tmpTrack;
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
