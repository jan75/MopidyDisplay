// artist.h++
#ifndef H_ARTIST
#define H_ARTIST
#include <QString>
#include <QSettings>
#include <QListWidgetItem>
#include <memory>
#include <iostream>
#include <json.h++>

class Artist {
    public:
        Artist(QString name);

        void set_name(QString name);
        QString get_name();

        bool compare(Artist artist);
        bool compare(std::shared_ptr<Artist> artist);

    private:
        QString name;
};

#endif
