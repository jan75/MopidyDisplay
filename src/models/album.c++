// album.c++
#include "album.h++"

Album::Album(QString name) {
    this->name = name;
}

void Album::set_name(QString name) {
    this->name = name;
}

QString Album::get_name() {
    return this->name;
}
