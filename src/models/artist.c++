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
