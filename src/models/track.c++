// track.c++
#include "track.h++"

Track::Track(QString title, std::shared_ptr<Album> album, std::vector<std::shared_ptr<Artist>> artists, int length, int track_number) {
    this->title = title;
    this->album = album;
    this->artists = artists;
    this->length = length;
    this->track_number = track_number;
    this->length_readable = length_to_str(length);
}

void Track::set_title(QString title) {
    this->title = title;
    calculate_object_hash();
}

void Track::set_album(std::shared_ptr<Album> album) {
    this->album = album;
}

void Track::set_artists(std::vector<std::shared_ptr<Artist>> artists) {
    this->artists = artists;
}

void Track::set_length(int length) {
    this->length = length;
    this->length_readable = length_to_str(length);
    calculate_object_hash();
}

void Track::set_track_number(int track_number) {
    this->track_number = track_number;
    calculate_object_hash();
}

QString Track::get_title() {
    return this->title;
}

std::shared_ptr<Album> Track::get_album() {
    return this->album;
}

std::vector<std::shared_ptr<Artist>> Track::get_artists() {
    return this->artists;
}

int Track::get_length() {
    return this->length;
}

QString Track::get_length_readable() {
    return this->length_readable;
}

int Track::get_track_number() {
    return this->track_number;
}

void Track::print() {
    std::cout << this->title.toStdString() << std::endl;
}

QString Track::length_to_str(int length) {
    int hours = 0;
    int minutes = 0;
    int seconds = length / 1000;
    while(seconds > 3600) {
        hours = hours + 1;
        seconds = seconds - 3600;
    }

    while(seconds > 60) {
        minutes = minutes + 1;
        seconds = seconds - 60;
    }

    QString readable_time("");
    if(hours != 0) {
        if(hours < 10) {
            readable_time.append("0");
            readable_time.append(QString::number(hours));
        } else {
            readable_time.append(QString::number(hours));
        }
        readable_time.append(":");
    }

    if(minutes != 0) {
        if(minutes < 10) {
            readable_time.append("0");
            readable_time.append(QString::number(minutes));
        } else {
            readable_time.append(QString::number(minutes));
        }
        readable_time.append(":");
    }

    if(seconds != 0) {
        if(seconds < 10) {
            readable_time.append("0");
            readable_time.append(QString::number(seconds));
        } else {
            readable_time.append(QString::number(seconds));
        }
    } else {
        readable_time.append("00:00");
    }
    return readable_time;
}

std::size_t Track::get_object_hash() {
    if(this->object_hash != 0) {
        return this->object_hash;
    } else {
        calculate_object_hash();
        return this->object_hash;
    }
}

void Track::calculate_object_hash() {
    std::size_t tmp_hashval = 0;
    std::hash<std::string> string_hash_function;
    std::hash<int> int_hash_function;



    tmp_hashval += string_hash_function(this->title.toStdString());
    tmp_hashval += int_hash_function(this->length);
    tmp_hashval += int_hash_function(this->track_number);

    this->object_hash = tmp_hashval;
}
