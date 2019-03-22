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

        static bool artist_compare(const std::shared_ptr<Artist> &a, const std::shared_ptr<Artist> &b);

        std::size_t get_object_hash();

    private:
        QString name;
        std::size_t object_hash;

        void calculate_object_hash();
};

#endif
